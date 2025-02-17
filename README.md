# Tencent Open Course
## Assignment
### 第一课
#### 1. UE5.3 源码版安装
<div align=center>
<img src="Assignments/Assignment_01/images/img1.png"><br>
</div>

&emsp;&emsp;报名公开课课前已经安装UE5.3.2源码版，并参与过腾讯图形学实践课，有一定的源码阅读、调试经验。<br>
<br>

#### 2. Android平台打包测试
<div align=center>
<img src="Assignments/Assignment_01/images/img2.png" width="480px"><br>
</div>

&emsp;&emsp;使用源码引擎创建第一人称工程，完成Android环境配置并打包apk在安卓手机上成功运行，运行操作录像及手机录屏见[Video][Link1]
<br>

#### 3. 课堂笔记
&emsp;&emsp;整理了一个XMind脑图笔记，见[Note][Link2]，对老师上课讲的一些UE debug方法做了代码实现，对引擎工具进行了使用并整理了用法，将课上提到的一些内容链接到XMind中我之前做的学习笔记，例如UE的Gameplay架构，UE的反射原理，UObject序列化等(类似下图)。之后所有的笔记都整理在该文件中。
<div align=center>
<img src="Assignments/Assignment_01/images/img4.png" width="480px"><br>
</div>

### 第二课
#### 1. 射击游戏demo

Demo演示视频见[Video][Link3]，简要说明如下

&emsp;&emsp;(1) 目标在指定包围盒区域内随机生成，普通目标值1分，有小概率生成高价值目标（金色材质），值2分，目标数量、目标分值、消灭目标需要的击中次数、高价值目标生成概率均可通过蓝图调整;

&emsp;&emsp;(2) 通过GameState控制对局流程，使用了简单的时间轴判断游戏阶段，如果游戏流程比较复杂可以使用有限状态机实现，我在其它项目有所实现。游戏流程分为准备阶段、对局阶段和结算阶段，各阶段时间均可通过蓝图设置，结算阶段玩家会失去控制权并进入慢动作模式;

&emsp;&emsp;(3) 实现了多人联机，在结算阶段通过一个ListView展示所有玩家排名、ID和分数，当出现分数相同玩家时，排名也会正确计算;

&emsp;&emsp;(4) 倒计时、分数、排名等数据通过UMG展示，使用Aseprite绘制了一个准星并应用在游戏中

<div align=center>
<img src="Assignments/Assignment_02/images/img2.png" width="360px"><br>
</div>

<div align=center>
<img src="Assignments/Assignment_02/images/img1.png" width="480px"><br>
</div>

&emsp;&emsp;(5) 核心代码文件见[source][Link4]，所有函数和属性的注释都写在头文件中

<div align=center>
<img src="Assignments/Assignment_02/images/img3.png" width="360px"><br>
</div>

#### 2. 课堂笔记

见[Note][Link2]

### 第三课
#### 1. UE标识符
UE标识符详解见大钊Github项目：https://github.com/fjz13/UnrealSpecifiers

所有标识符按类名、功能模块分类，每个标识符文档内容包含基本信息、常用程度、示例代码等。

<div align=center>
<img src="Assignments/Assignment_03/images/img1.png" width="200px">&emsp;
<img src="Assignments/Assignment_03/images/img2.png" width="336px"><br>
</div>
<div align=center>

</div>
<div align=center>
<img src="Assignments/Assignment_03/images/img3.png" width="552px"><br>
</div>

#### 2. 课堂笔记

见[Note][Link2]

### 第四课
#### 1. 登录UI
使用UMG实现游戏登陆界面，界面包括用户名、密码输入框，注册、登录按钮，实现伪加载界面，如下图，运行演示见[Video][Link5]。

<div align=center>
<img src="Assignments/Assignment_04/images/img1.png" width="552px"><br>
</div>
<div align=center>
<img src="Assignments/Assignment_04/images/img2.png" width="552px"><br>
</div>

#### 2. 课堂笔记

见[Note][Link2]

### 第五课
#### 1. 敌人动画
使用动画蓝图实现敌人行走、死亡动画，如下图，运行演示见[Video][Link6]。
<div align=center>
<img src="Assignments/Assignment_05/images/img1.png" width="552px"><br>
</div>

#### 2. 课堂笔记

见[Note][Link2]

### 第六课
#### 1. RenderDoc分析
见笔记[Note][Link2]中第一课的笔记，有对RenderDoc的使用实例。

#### 2. 基于法线、边缘检测和深度检测的描边feature
预览效果如下图。
<div align=center>
<img src="Assignments/Assignment_06/images/img4.png" width="552px"><br>
</div>
后处理材质蓝图如下图。
<div align=center>
<img src="Assignments/Assignment_06/images/img5.png" width="552px"><br>
</div>

较简单的outline可基于法线实现，但其不适用于垂直于屏幕的几何体平面，故引入了边缘检测和深度检测
##### 基于法线的outline
<div align=center>
<img src="Assignments/Assignment_06/images/img1.png" width="552px"><br>
</div>

##### 基于边缘检测的outline
使用kernel进行深度检测，下图是获取kernel的材质函数。
<div align=center>
<img src="Assignments/Assignment_06/images/img2.png" width="552px"><br>
</div>

##### 深度检测以解决法线outline的问题
由于垂直于屏幕的几何体平面整个会被认为是边缘，故引入深度检测
<div align=center>
<img src="Assignments/Assignment_06/images/img3.png" width="552px"><br>
</div>

#### 2. 课堂笔记

见[Note][Link2]


### 第七课
#### 1. 敌人AI
使用行为树实现敌人巡逻AI，目前因时间关系未实现敌人索敌的逻辑，运行演示见[Video][Link7]。



[Link1]:Assignments/Assignment_01/videos
[Link2]:Note.xmind
[Link3]:Assignments/Assignment_02/videos
[Link4]:Assignments/Assignment_02/source
[Link5]:Assignments/Assignment_04/videos
[Link6]:Assignments/Assignment_05/videos
[Link7]:Assignments/Assignment_07/videos