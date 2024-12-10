#!/bin/bash
SERVICE_DIR="./services"
mkdir -p $SERVICE_DIR

cat <<EOF > $SERVICE_DIR/safeboot
#!/sbin/openrc-run
name=safeboot
command=/sbin/insmod
command_args=/lib/modules/$(uname -r)/extra/safeboot.ko
pidfile=/run/${name}.pid

depend() {
    need localmount
}
EOF

chmod +x $SERVICE_DIR/safeboot
echo "OpenRC service file created at $SERVICE_DIR/safeboot"
