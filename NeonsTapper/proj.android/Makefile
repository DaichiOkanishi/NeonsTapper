main_d:
	bash build_native.sh

main_r:
	bash build_native_release.sh

d:
	bash build_native.sh
	ant debug

r:
	bash build_native_release.sh
	ant release

di:
	bash build_native.sh
	ant debug install
	adb shell am start -n jp.ryubise.neonsTapper/.neonsTapper

ri:
	bash build_native_release.sh
	ant release install
	adb shell am start -n jp.ryubise.neonsTapper/.neonsTapper

rdi:
	bash build_native.sh
	ant release install
	adb shell am start -n jp.ryubise.neonsTapper/.neonsTapper

clean:
	bash build_native.sh clean
	ant clean

u:
	ant uninstall
