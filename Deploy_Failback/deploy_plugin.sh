#!/bin/bash
ROUTER=root@DEFAULT-GATEWAY-IP

sed -i 's/\r$//' rc.local failback.sh watchdog_launcher.sh 

scp rc.local failback.sh watchdog_launcher.sh $ROUTER:/tmp/ && \

ssh $ROUTER '
    mv /tmp/rc.local /etc/rc.local &&
    mv /tmp/failback.sh /overlay/failback.sh &&
    mv /tmp/watchdog_launcher.sh /overlay/watchdog_launcher.sh &&
    chmod +x /etc/rc.local /overlay/failback.sh /overlay/watchdog_launcher.sh
    /overlay/watchdog_launcher.sh &
'

echo "Deployment complete!"
