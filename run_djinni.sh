#! /usr/bin/env bash

base_dir=$(cd "`dirname "0"`" && pwd)

djinni_file="gearsbox.djinni"
generated_dir="generated-src"

if [ "$1" = "test" ];then
   generated_dir="test"
   djinni_file="test.djinni"
   echo $generated_dir
fi

cpp_out="$base_dir/$generated_dir/cpp"
cpp_extended="$base_dir/src/ui/"
jni_out="$base_dir/$generated_dir/jni"
objc_out="$base_dir/$generated_dir/objc"
java_out="$base_dir/$generated_dir/java/dyno/fun/gearsbox"
yaml_out="$base_dir/$generated_dir/yaml"
java_package="dyno.fun.gearsbox"
namespace="gearsbox"
objc_prefix="GB"

deps/djinni/src/run \
   --java-out $java_out \
   --java-package $java_package \
   --ident-java-field mFooBar \
   \
   --cpp-out $cpp_out \
   --cpp-namespace $namespace \
   --cpp-optional-template "std::experimental::optional" \
   --cpp-optional-header "<experimental/optional>" \
   \
   --jni-out $jni_out \
   --ident-jni-class NativeFooBar \
   --ident-jni-file NativeFooBar \
   \
   --objc-out $objc_out \
   --objc-type-prefix $objc_prefix \
   \
   --objcpp-out $objc_out \
   \
   --yaml-out "$yaml_out/yaml" \
   --yaml-out-file "yaml-gearsbox.yaml" \
   --yaml-prefix "gb_" \
   \
   --idl $djinni_file
