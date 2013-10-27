CCSpriteFX
====================

Cocos2d-x color and texture transform effect extension.


功能
-------------------
   * 支持Flash的经典插值(Motion)动画
   * 支持Flash的引导层动画(通过JSFL进行转换为关键帧实现)
   * 支持Flash的所有Color Effect
   * 支持MovieClip和Graphics的2D矩阵变换(缩放，旋转，切变，偏移，锚点)
   * 自动将MovieClip的原点每帧更新为CCNode的AnchorPoint坐标
   * 自动更新每帧的BoundingBox
   * 播放动画操作实现为Action类
   * 通过缓存提高加载和动画计算的速度
   * 支持Flash中MovieClip的嵌套
   * 支持Graphics的所有循环播放模式
   * 支持自定义动画事件


依赖
-------------------
   * cocos2d-x v3.0 以上


编译demo
------------------
   * 使用`git submodule init`和`git submodule update`下载cocos2d-x


整合cocos2d-x
-----------------
   * 将CCSpriteFX目录复制到extensions目录下
   * 在cocos-ext.h中加入
   
```c++
// CCSpriteFX
#include "CCSpriteFX/CCSpriteFX.h"
#include "CCSpriteFX/CCActionTextureTransform.h"
#include "CCSpriteFX/CCActionColorMatrix.h"
```


使用方法
-----------------
   * 详见demo的测试代码

