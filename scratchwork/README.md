practice
========

I often make simple use of assert in java, when attempting to run a class use "java -ea" -ea means "enable asserts".

The classes with main() that can be executed on jvm usually have all other classes it needs in the same directory. In some cases I make use of classes in practice/util directory. I've setup packages so that the sequence of java commands to execute a class is:

from the directory where this repo was cloned (practice is newly created subdirectory from git clone):
* javac -cp . practice/util/javaSourceFileList
* javac -cp . practice/someDir/javaSourceFileList
* java -cp . -ea practice/someDir/className
