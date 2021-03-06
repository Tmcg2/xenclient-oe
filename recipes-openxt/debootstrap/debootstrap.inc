LICENSE = "CLOSED"
PSTAGING_DISABLED = "1"
XENCLIENT_BUILD_SRC_PACKAGES = "0"

SSTATETASKS= ""

SRC_URI = "${OPENXT_MIRROR}/debootstrap_${DEBOOTSTRAP_SUITE}_${DEBOOTSTRAP_ARCH}_${PV}.tar.gz"

S = "${WORKDIR}/${DEBOOTSTRAP_SUITE}_${DEBOOTSTRAP_ARCH}"
	

python do_clean_append() {
	staging_dir = "%s/debootstrap/%s_%s" % (bb.data.getVar('STAGING_DIR',d,1), bb.data.getVar('DEBOOTSTRAP_SUITE',d,1), bb.data.getVar('DEBOOTSTRAP_ARCH', d,1))
	os.system("[ -d '%s' ] && sudo rm -rf --one-file-system '%s'" % (staging_dir, staging_dir))
}


do_unpack() {
	:
}

do_configure() {
	:
}

do_compile() {
	:
}

#do_stage(){
#	out="${STAGING_DIR_TARGET}/usr/share/debootstrap/${DEBOOTSTRAP_SUITE}_${DEBOOTSTRAP_ARCH}"
#	mkdir -p "${STAGING_DIR_TARGET}/usr/share/debootstrap/${DEBOOTSTRAP_SUITE}_${DEBOOTSTRAP_ARCH}"
#	cd "${S}" && rsync -a . "${out}" 
#}

python do_install() {
	import sys, os
	localdata = bb.data.createCopy(d)
	bb.data.update_data(localdata)
	src_uri = bb.data.getVar('SRC_URI', localdata)
	if not src_uri:
		return
	src_uri = bb.data.expand(src_uri, localdata)
	local = bb.data.expand(bb.fetch.localpath(src_uri, localdata), localdata)
	stage_dir  = "%s/debootstrap/" % (bb.data.getVar('STAGING_DIR',d,1),)
	chroot_dir = "%s/%s_%s" % (stage_dir, bb.data.getVar('DEBOOTSTRAP_SUITE',d,1), bb.data.getVar('DEBOOTSTRAP_ARCH', d,1))
	if os.path.isdir(chroot_dir):
		return
	os.system("mkdir -p '%s'" % (stage_dir,))
	bb.note("Executing cd '%s' && sudo tar xzpkf '%s'" % (stage_dir, local))
	os.system("cd '%s' && ( exec 1>&2; pwd; echo ' debootstrap un-tarring';  exit 0 ) &&  sudo tar xzpkf '%s'" % (stage_dir, local))
	os.system("cd '%s/' && ( sudo mkdir ./dev; sudo rm -f ./dev/null; exit 0 ) && sudo mknod ./dev/null c 1 3 && sudo chmod 666 ./dev/null" % (chroot_dir,))
	bb.note("UN-TARRING FINISHED")

}

do_package_write() {
	:
}

do_package_ipk() {
	:
}
