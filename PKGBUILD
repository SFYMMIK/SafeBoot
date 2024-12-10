# Maintainer: Your Name <your.email@example.com>
pkgname=safeboot
pkgver=1.0.0
pkgrel=1
pkgdesc="SafeBoot: A kernel module to protect Linux from bootkits"
arch=('x86_64')
url="https://yourprojecturl.com"
license=('GPL')
depends=('linux' 'tpm2-tools')
makedepends=('linux-headers')
source=("git+https://github.com/SFYMMIK/SafeBoot.git")
md5sums=('SKIP')

pkgdir="$srcdir/$pkgname"

build() {
    cd "$srcdir/$pkgname"
    make
}

package() {
    cd "$srcdir/$pkgname"

    install -Dm644 safeboot.ko "$pkgdir/usr/lib/modules/$(uname -r)/extra/safeboot.ko"

    install -d "$pkgdir/etc/systemd/system"
    install -Dm644 services/safeboot.service "$pkgdir/etc/systemd/system/safeboot.service"

    install -d "$pkgdir/etc/init.d"
    install -Dm644 services/safeboot "$pkgdir/etc/init.d/safeboot"

    install -d "$pkgdir/etc/service"
    install -Dm644 services/safeboot/run "$pkgdir/etc/service/safeboot/run"

    install -Dm755 create_systemd_service.sh "$pkgdir/usr/bin/create_systemd_service.sh"
    install -Dm755 create_openrc_service.sh "$pkgdir/usr/bin/create_openrc_service.sh"
    install -Dm755 create_runit_service.sh "$pkgdir/usr/bin/create_runit_service.sh"
}

# Optionally, add `install` function if you want post-install actions, e.g., enabling services

# End of PKGBUILD
