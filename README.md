# QtCV_With_CMake
Example: Develop application with &lt;Qt + CMake + OpenCV>, Witch supports Linux and Android.

## 1.0.0
- 作为Demo项目已经完成
- 该探索的功能点都已经走顺
- Mat 2 QImage 坑点确实大
- provider 的报错可能与上一条有关但换成Pointer似乎更好
- Mac系和Win没有做兼容但方法类似

## 发现的问题
### provider_crash_version
这种容易crash，ubuntu&android都是莫名其妙，尤其是抛出图片比较大的时候。实现方法姑且用这个分支记录.

也可能与Mat2QImage方式有关

主分支已经换成Point的方式，也出现了crash的情况。修改了转换方法之后现在稳定。