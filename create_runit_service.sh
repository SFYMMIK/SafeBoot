#!/bin/bash
SERVICE_DIR="./services"
mkdir -p $SERVICE_DIR

cat <<EOF > $SERVICE_DIR/safeboot/run
#!/bin/sh
insmod /lib/modules/$(uname -r)/extra/safeboot.ko
EOF

chmod +x $SERVICE_DIR/safeboot/run
echo "Runit service file created at $SERVICE_DIR/safeboot/run"
