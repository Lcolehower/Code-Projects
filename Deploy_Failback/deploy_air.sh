#!/bin/bash

# Prompt user for input
read -p "Enter router IP address: " ROUTER_IP
read -p "Enter SSH username: " USERNAME

ROUTER="$USERNAME@$ROUTER_IP"

echo "Attempting SSH connection to $ROUTER..."

# Test SSH connection
ssh -o ConnectTimeout=5 "$ROUTER" "exit"

if [ $? -ne 0 ]; then
    echo "SSH connection failed. Check IP/username or network."
    exit 1
fi

echo "Connection successful. Starting deployment..."

# Fix line endings
sed -i 's/\r$//' rc.local failback.sh watchdog_launcher.sh

# Copy files
scp rc.local failback.sh watchdog_launcher.sh "$ROUTER:/tmp/" || {
    echo "File transfer failed."
    exit 1
}

# Run remote commands
ssh "$ROUTER" '
    mv /tmp/rc.local /etc/rc.local &&
    mv /tmp/failback.sh /overlay/failback.sh &&
    mv /tmp/watchdog_launcher.sh /overlay/watchdog_launcher.sh &&
    chmod +x /etc/rc.local /overlay/failback.sh /overlay/watchdog_launcher.sh &&
    /overlay/watchdog_launcher.sh &
'

echo "Deployment complete!"
