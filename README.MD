the third party codes and utilities used in projects  

###party codes dependence  
1. curl  
2. libuv  
3. zf_log  
4. jsoncpp  
5. sqlit3  
6. ~~protobuf~~
7. breakpad
8. gtest

###interface for c++   
1. IHttpRequest.h  
2. ILog.h  
3. json.h  

###interface for j/o  
1. gearbox_log  
2. async_loop  
3. callback_i64str, need to be implement in j/o  

this should be a sub folder in clent project, I will modify USNIT as as sample  

1. add gearsbox to clent, in root of client directory run the command below

	git submodule add https://github.com/oldmannt/gearsbox.git gearsbox

update the submodule of gearsbox

	cd gearsbox
	git submodule init
	git submodule update
	
	git submodule add https://github.com/dropbox/djinni.git deps/djinni
	git submodule add https://chromium.googlesource.com/external/gyp.git deps/gyp
	cd deps/gyp
	git checkout -q 0bb67471bca068996e15b56738fa4824dfa19de0
	
2. ~~protobuf as ui config~~
	~~create .proto file, genrate protco c++ and python code, used pyton to write binary like config, read by c++.~~  
	~~gearsbox use protobuf as ui config, let me think about that may be make a probability to build ui by server.~~
	~~current version is protobuf-3.0.0-beta-3, compiler and tester code were detele~~

2. create client.djinni, client.gyp, run_djinni.sh in clent
	
	#generate the bridge code and project
	make ios_proj
	make android_proj

3. create client.xcworkspace in ios
	open client.xcworkspace, add client.xcodeproj

4. create ios applicaton project, and add to the xcworkspace
	build and test

5. create a android studio project in android/usnit
	~~use gradle-experimental builed client_jni.so~~
	use cmakelist to build ndk
	config build.gradle, app/build.gradle gradle/wrapper/gradle-wrapper.properties
	build and test

6. make

### protubuf


.####more infomation  about android gradle build
http://ph0b.com/android-studio-gradle-and-ndk-integration/
http://ph0b.com/new-android-studio-ndk-support/  
http://www.slideshare.net/ph0b/mastering-the-ndk-with-android-studio-and-the-gradleexperimental-plugin  
http://tools.android.com/tech-docs/new-build-system/gradle-experimental  
https://codelabs.developers.google.com/codelabs/android-studio-jni/index.html?index=..%2F..%2Findex#0  
