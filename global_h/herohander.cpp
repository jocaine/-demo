﻿#include"herohander.h"
heroHander::heroHander()
{
   heroData* caocao       =new heroData{QPixmap("://figpic/caocao.jpg"),  QPixmap("://figpic/c_caocao.jpg")};
    caocao->skills.append(new skill("奸雄","获得伤害牌",2));
    caocao->skills.append(new skill("护驾","其他玩家代替出闪",1));
   heroData* daqiao       =new heroData{QPixmap("://figpic/daiqiao.jpg"),  QPixmap("://figpic/c_daqiao.jpg")};
    daqiao->skills.append(new skill("国色","方片牌当作乐不思蜀",2));
    daqiao->skills.append(new skill("流离","弃一张牌转移杀",2));
   heroData* diaochan     =new heroData{QPixmap("://figpic/diaochan.png"),QPixmap("://figpic/c_diaochan.jpg")};
   diaochan->skills.append(new skill("离间","让两名玩家决斗",2));
   diaochan->skills.append(new skill("闭月","回合结束摸一张牌",1));
   heroData* gannin       =new heroData{QPixmap("://figpic/gannin.jpg"),  QPixmap("://figpic/c_ganning.jpg")};
   gannin->skills.append(new skill("奇袭","黑桃和梅花当作过河拆桥使用",3));
   heroData* guanyu       =new heroData{QPixmap("://figpic/guanyu.jpg"),  QPixmap("://figpic/c_guanyu.png")};
    guanyu->skills.append(new skill("武圣","红心或方片当杀打出",3));
   heroData* guojia       =new heroData{QPixmap("://figpic/guojia.jpg"),  QPixmap("://figpic/c_guojia.jpg")};
   guojia->skills.append(new skill("天妒","你的判定牌生效后获得他",1));
   guojia->skills.append(new skill("遗计","收到一点伤害摸两张牌随意分配",3));
   heroData* huanggai     =new heroData{QPixmap("://figpic/huanggai.jpg"),QPixmap("://figpic/c_huanggai.jpg")};
   huanggai->skills.append(new skill("苦肉","主动掉一滴血摸两张牌",3));
   heroData* huangyueyin  =new heroData{QPixmap("://figpic/huangyueyin.jpg"),QPixmap("://figpic/c_huangyueyin.png")};
   huangyueyin->skills.append(new skill("集智","使用非延时锦囊时摸一张牌",3));
   huangyueyin->skills.append(new skill("奇才","锦囊无距离限制",1));
   heroData* huatuo       =new heroData{QPixmap("://figpic/huatuo.jpg"),     QPixmap("://figpic/c_huatuo.jpg")};
   huatuo->skills.append(new skill("急救","出牌阶段，弃一张手牌任意一名角色回复一点血（回合限一次）",2));
   huatuo->skills.append(new skill("青囊","出牌阶段，弃一张手牌任意一名角色回复一点血（回合限一次）",1));
   heroData* liubei       =new heroData{QPixmap("://figpic/liubei.jpg"),     QPixmap("://figpic/c_liubei.jpg")};
   liubei->skills.append(new skill("仁德","给手牌，大于两张时一滴回血",2));
   liubei->skills.append(new skill("激将","其他玩家替你出杀",1));
   heroData* luxun        =new heroData{QPixmap("://figpic/luxun.jpg"),      QPixmap("://figpic/c_luxun.jpg")};
   luxun->skills.append(new skill("谦逊","不能成为乐不思蜀和顺手牵羊的目标",3));
   luxun->skills.append(new skill("连营","失去最后一张手牌时摸一张",1));
   heroData* lvbu         =new heroData{QPixmap("://figpic/lvbu.jpg"),       QPixmap("://figpic/c_lvbu.jpg")};
   lvbu->skills.append(new skill("无双","杀和决斗需要两张牌才能抵消",3));
   heroData* lvmeng       =new heroData{QPixmap("://figpic/lvmeng.jpg"),     QPixmap("://figpic/c_lvmeng.jpg")};
   lvmeng->skills.append(new skill("克己","出牌阶段没使用或打出过杀时可以屯牌",3));
   heroData* machao       =new heroData{QPixmap("://figpic/machao.jpg"),     QPixmap("://figpic/c_machao.jpg")};
   machao->skills.append(new skill("马术","计算距离-1",1));
   machao->skills.append(new skill("铁骑","使用杀可以进行判定，若为红桃或方片则不可闪避",2));
   heroData* simayi       =new heroData{QPixmap("://figpic/simayi.jpg"),     QPixmap("://figpic/c_simayi.jpg")};
   simayi->skills.append(new skill("反馈","从伤害来源处获取一张牌",2));
   simayi->skills.append(new skill("鬼才","改判",2));
   heroData* sunshangxiang=new heroData{QPixmap("://figpic/sunshangxiang.jpg"),QPixmap("://figpic/c_sunshangxiang.jpg")};
   sunshangxiang->skills.append(new skill("结姻","出牌阶段，弃两张手牌和一名受伤玩家共同回一滴血",1));
   sunshangxiang->skills.append(new skill("枭姬","失去装备时摸两张牌",3));
   heroData* sunquan      =new heroData{QPixmap("://figpic/sunquan.jpg"),      QPixmap("://figpic/c_sunxuan.jpg")};
   sunquan->skills.append(new skill("制衡","换牌",2));
   sunquan->skills.append(new skill("救援","其他角色在你病死时使用桃可额外回复一点血量",1));
   heroData* xiahoudun    =new heroData{QPixmap("://figpic/xiahoudun.jpg"),    QPixmap("://figpic/c_xiahoudun.jpg")};
   xiahoudun->skills.append(new skill("刚烈","收到伤害时，可以判定，不为红心时，对方二选一：掉一滴血或弃两张牌",3));
   heroData* xuchu        =new heroData{QPixmap("://figpic/xuchu.jpg"),        QPixmap("://figpic/c_xuchu.jpg")};
   xuchu->skills.append(new skill("裸衣","摸牌阶段少摸一张牌，杀和决斗的伤害+1",2));
   heroData* zhangfei     =new heroData{QPixmap("://figpic/zhangfei.jpg"),     QPixmap("://figpic/c_zhangfei.jpg")};
   zhangfei->skills.append(new skill("咆哮","诸葛连弩",3));
   heroData* zhangliao    =new heroData{QPixmap("://figpic/zhangliao.jpg"),    QPixmap("://figpic/c_zhangliao.jpg")};
   zhangliao->skills.append(new skill("突袭","摸牌阶段，从其他两名玩家手牌中摸牌",3));
   heroData* zhaoyun      =new heroData{QPixmap("://figpic/zhaoyun.jpg"),      QPixmap("://figpic/c_zhaoyun.jpg")};
   zhaoyun->skills.append(new skill("龙胆","杀当闪，闪当杀",2));
   heroData* zhenji       =new heroData{QPixmap("://figpic/zhenji.jpg"),       QPixmap("://figpic/c_zhenji.jpg")};
   zhenji->skills.append(new skill("倾国","黑桃或梅花当闪打出",2));
   zhenji->skills.append(new skill("洛神","摸牌时判定，判定牌为黑桃和梅花时获得，并且继续判定",3));
   heroData* zhouyu       =new heroData{QPixmap("://figpic/zhouyu.jpg"),       QPixmap("://figpic/c_zhouyu.jpg")};
   zhouyu->skills.append(new skill("英姿","摸牌时多摸一张",2));
   zhouyu->skills.append(new skill("反间","猜花色",2));
   heroData* zhugeliang   =new heroData{QPixmap("://figpic/zhugeliang.jpg"),   QPixmap("://figpic/c_zhugeliang.jpg")};
   zhugeliang->skills.append(new skill("观星"," 观测牌x张，最多五张",3));
   zhugeliang->skills.append(new skill("空城","没有手牌不可以成为杀和决斗的目标",1));
   heroLib<<caocao<<daqiao<<diaochan<<gannin<<guanyu<<guojia<<huanggai<<huangyueyin<<huatuo<<liubei<<luxun<<lvbu<<lvmeng<<machao<<simayi<<sunshangxiang
           <<sunquan<<xiahoudun<<xuchu<<zhangfei<<zhangliao<<zhaoyun<<zhenji<<zhouyu<<zhugeliang;

}
