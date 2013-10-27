CCSpriteFX
====================

Cocos2d-x color and texture transform effect extension.


功能
-------------------
   * 精灵的显示颜色取反，原色缩放，原色偏移，亮度，饱和度，对比度，阈值，色相偏移动画
   * 精灵的纹理坐标偏移，旋转，缩放，切变动画


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

