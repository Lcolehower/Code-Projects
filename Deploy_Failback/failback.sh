#!/bin/sh

# --- CONFIG ---
PRIMARY_IF="wwan0"        # Cellular
SECONDARY_IF="wlan0"      # WiFi
TARGET="IP TARGET ADDRESS"

CHECK_GAP=30              # Main loop interval
STABLE_WAIT=30            # Stability check before switching
HEARTBEAT_INTERVAL=300    # 5 minutes

LOGFILE="/tmp/failback.log"
PIDFILE="/var/run/failback.pid"

# --- Single instance protection ---
if [ -f "$PIDFILE" ] && kill -0 "$(cat "$PIDFILE")" 2>/dev/null; then
    exit 0
fi

echo $$ > "$PIDFILE"
trap "rm -f $PIDFILE; exit" INT TERM EXIT

echo "$(date): Failback started (PID $$)" >> "$LOGFILE"

STATE="unknown"
LAST_HEARTBEAT=$(date +%s)

# --- Helper: current default interface ---
current_default() {
    ip route show default 2>/dev/null | awk '{print $5}'
}

# --- Main loop ---
while true; do
    NOW=$(date +%s)

    # --- Heartbeat logging ---
    if [ $((NOW - LAST_HEARTBEAT)) -ge "$HEARTBEAT_INTERVAL" ]; then
        CUR_IF="$(current_default)"
        echo "$(date): Heartbeat: state=$STATE, default=${CUR_IF:-none}" >> "$LOGFILE"
        LAST_HEARTBEAT="$NOW"
    fi

    # --- Primary check ---
    if ping -c 1 -W 1 -I "$PRIMARY_IF" "$TARGET" >/dev/null 2>&1; then
        if [ "$STATE" != "primary" ]; then
            sleep "$STABLE_WAIT"

            if ping -c 1 -W 1 -I "$PRIMARY_IF" "$TARGET" >/dev/null 2>&1; then
                CUR_IF="$(current_default)"

                if [ "$CUR_IF" != "$PRIMARY_IF" ]; then
                    ip route replace default dev "$PRIMARY_IF"
                    echo "$(date): Switched default → $PRIMARY_IF" >> "$LOGFILE"
                fi

                STATE="primary"
            fi
        fi
    else
        if [ "$STATE" != "secondary" ]; then
            CUR_IF="$(current_default)"

            if [ "$CUR_IF" != "$SECONDARY_IF" ]; then
                ip route replace default dev "$SECONDARY_IF"
                echo "$(date): Fallback → $SECONDARY_IF" >> "$LOGFILE"
            fi

            STATE="secondary"
        fi
    fi

    sleep "$CHECK_GAP"
done
