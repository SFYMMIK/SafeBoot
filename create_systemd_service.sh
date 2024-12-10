#!/bin/bash
SERVICE_DIR="./services"
mkdir -p $SERVICE_DIR

cat <<EOF > $SERVICE_DIR/safeboot.service
[Unit]
Description=SafeBoot: Bootkit Protection for Linux
After=network.target

[Service]
Type=oneshot
ExecStart=/usr/sbin/insmod /lib/modules/$(uname -r)/extra/safeboot.ko
ExecStop=/usr/sbin/rmmod safeboot
RemainAfterExit=true

[Install]
WantedBy=multi-user.target
EOF

echo "Systemd service file created at $SERVICE_DIR/safeboot.service"
