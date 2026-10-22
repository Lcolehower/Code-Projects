#!/bin/sh

WATCHDOG_LOG="/var/log/watchdog.log"
FAILBACK_SCRIPT="/overlay/failback.sh"
PIDFILE="/var/run/watchdog_launcher.pid"

mkdir -p /var/run

# --- Prevent duplicate watchdog ---
if [ -f "$PIDFILE" ] && kill -0 "$(cat "$PIDFILE")" 2>/dev/null; then
    exit 0
fi

echo $$ > "$PIDFILE"
trap "rm -f $PIDFILE; exit" INT TERM EXIT

echo "$(date): Watchdog started (PID $$)" >> "$WATCHDOG_LOG"

while true; do
    if [ -f "/var/run/failback.pid" ] && kill -0 "$(cat /var/run/failback.pid)" 2>/dev/null; then
        :
    else
        echo "$(date): Failback missing → restarting" >> "$WATCHDOG_LOG"
        "$FAILBACK_SCRIPT" &
    fi

    sleep 30
done
