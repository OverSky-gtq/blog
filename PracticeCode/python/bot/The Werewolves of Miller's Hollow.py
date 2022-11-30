from nonebot.plugin import on_command,on_keyword
from nonebot.adapters.onebot.v11 import Bot, Event,GroupMessageEvent,PrivateMessageEvent
import time
from nonebot import on_regex
from nonebot.params import RegexMatched
import random

class id:
    def __init__(self,n,p):
         self.name = n
         self.isPostive = p

class player:
    def __init__(self,qq,name):
        self.qq = int(qq)
        self.name = name
        self.idlist = []
        

def get_id(QQ):  #传入QQ号查询生效身份
    global all_players
    for person in all_players:
        if person.qq == QQ:
            return person.idlist[0].name
    return "空"
temp = "" # 临时用
idlists = [id("平民",True),id("狼人",False),id("隐狼",False),id("盗贼",True),id("平民",True),id("女巫",True),id("猎人",True),id("平民",True),id("平民",True),id("守卫",True),id("平民",True),id("预言家",True)]
stage = "初始" # 阶段开关
master = ["2698595115",]
groupid = 0 #游戏进行群号
red = [] # 坏人player列表
blue = [] # 金宝宝player列表
all_players = [player(1971458550,"花伞"),player(2698595115,"OverSky"),player(2835814593,"忆"),player(1852638727,"眷顾"),player(2251839300,"小花"),player(2194297670,"口")] #所有玩家集合
playlist = "" #展示玩家列表，便于查看局势

clear = on_command('洗牌')
@clear.handle()
async def _(bot: Bot,event: GroupMessageEvent):
    global idlists
    await clear.send("进行洗牌")
    flag = True
    while(flag):  # 防止预言家和坏人在一起
        flag = False
        random.shuffle(idlists)
        for i in range(0,12,2):
            s = {idlists[i],idlists[i+1]}
            if (s=={id("狼人",False),id("预言家",True)}) or (s=={id("预言家",True),id("隐狼",False)}):
                flag = True
                await clear.send("预言家不能和坏人在一起，重新洗牌")
                break
    await clear.finish("洗牌结束")

start = on_command('开始游戏')
@start.handle()
async def _(bot: Bot,event: GroupMessageEvent):
    global stage
    global master
    global groupid
    global red
    global blue
    global all_players
    global playlist
    if event.get_user_id() in master and stage=="初始":
        groupid = event.group_id
        await start.finish("进入准备阶段，招募六名玩家\n"+"加入游戏")

join = on_command('加入游戏')
@join.handle()
async def _(bot: Bot,event: GroupMessageEvent):
    global stage
    global master
    global groupid
    global red
    global blue
    global all_players
    global playlist
    qq = event.get_user_id()
    for i in all_players:
        if i.qq == int(qq):
            await join.finish("不可重复加入")

    if len(all_players) < 6:        
        temp = await bot.get_stranger_info(user_id=qq)
        name = temp["nickname"]
        all_players.append(player(qq,name))
        playlist += name +'(' + str(qq) + ')'+'\n'
        await join.send("加入成功("+str(len(all_players))+'/6)\n'+playlist)
    else:
        await join.finish("已满6人")


distribute = on_command('发牌')
@distribute.handle()
async def _(bot: Bot,event: Event):
    global stage
    global master
    global groupid
    global red
    global blue
    global all_players
    global playlist
    global idlists
    if event.get_user_id() in master and len(all_players) == 6:
        i = 0
        stage = '发牌'
        for person in all_players:
            a = idlists[i]
            b = idlists[i+1]
            if a.name == "盗贼": #处理盗贼卡，进行复制
                a = b
                await bot.send_private_msg(user_id=person.qq,message="你抽到了盗贼卡，已进行复制",auto_escape=True)
            if b.name == "盗贼":
                b = a
                await bot.send_private_msg(user_id=person.qq,message="你抽到了盗贼卡，已进行复制",auto_escape=True)
            person.idlist.append(a)
            person.idlist.append(b)
            if not a.isPostive or not b.isPostive:
                red.append(person)  #标记坏人
            if a.name=="平民" and b.name=="平民":
                blue.append(person) #标记金宝宝                               
            i += 2
            await bot.send_private_msg(user_id=person.qq,message="上牌:"+a.name+'\n'+"下牌:"+b.name+'\n发送[切牌]切换卡牌位置')
    else:
        await distribute.finish("你无权操作或人数不足")
        

get = on_command("查看身份牌")
@get.handle()
async def _(bot: Bot,event: PrivateMessageEvent):
    global all_players
    for person in all_players:
        if person.qq == int(event.get_user_id()):
            await get.finish("上牌:"+person.idlist[0].name+'\n'+"下牌:"+person.idlist[1].name+'\n发送[切牌]切换卡牌位置')
   

switch = on_command('切牌')
@switch.handle()
async def _(bot: Bot,event:PrivateMessageEvent):
    global stage
    global master
    global groupid
    global red
    global blue
    global all_players
    global playlist
    if stage == '发牌':
        for person in all_players:
            if person.qq == int(event.get_user_id()):
                temp = person.idlist[0]
                person.idlist[0] = person.idlist[1]
                person.idlist[1] = temp
                await switch.finish("上下牌位置切换成功\n"+"上牌:"+person.idlist[0].name+'\n'+"下牌:"+person.idlist[1].name)
    else:
        await switch.finish("当前阶段不可进行切牌")
guard_target = "0"
kill_target = []
check_target = "0"
poison_target = "0"
save_target = "0"

night = on_command('天黑了')
@night.handle()
async def _(bot: Bot,event: Event):
    global stage
    global master
    global groupid
    global red
    global blue
    global all_players
    global playlist
    if (stage == "发牌" or stage == "白天") and event.get_user_id() in master:
        stage = "守卫睁眼"
        await night.send("守卫请睁眼，你有40s时间选择你今晚要守护的人(包括自己)，不能连续两晚守同一人\n"+"[守qq]")
        #await bot.send_group_msg(playlist)
        time.sleep(40)
        stage = "狼人睁眼"
        await night.send("狼人请睁眼，你们有75s时间选择要杀的人，若意见不一致则无人死亡\n"+"[杀qq]")
        #await bot.send_group_msg(playlist)
        time.sleep(75)
        stage = "预言家睁眼"
        await night.send("预言家请睁眼，你有40s时间选择要查验的人\n"+"[查qq]")
        #await bot.send_group_msg(playlist)
        time.sleep(40)
        stage = "女巫睁眼"
        await night.send("女巫请睁眼，你有40s时间选择用药的人\n"+"[救人]\n"+"[毒qq]")
        #await bot.send_group_msg(playlist)
        time.sleep(40)
        stage = "白天"

guard = on_regex("守[0-9]+")
@guard.handle()
async def _(bot: Bot,event:PrivateMessageEvent,foo: str = RegexMatched()):
    global guard_target
    global stage
    global master
    global groupid
    global red
    global blue
    global all_players
    global playlist
    if stage=="守卫睁眼" and get_id(event.get_user_id())=="守卫":
        guard_target = foo[1:]
        await guard.send("守卫目标确认，请静候")

kill = on_regex("杀[0-9]+")
@kill.handle()
async def _(bot: Bot,event:PrivateMessageEvent,foo: str = RegexMatched()):
    global kill_target
    global stage
    global master
    global groupid
    global red
    global blue
    global all_players
    global playlist
    global temp
    for person in all_players:
        if person.qq == event.get_user_id():
            temp = person.idlist[1].name
    first = get_id(event.get_user_id())
    if stage=="狼人睁眼" and (first=="狼人" or first=="隐狼" or temp=="隐狼"):
        kill_target = foo[1:]
        await guard.send("被刀目标确认，请静候，若你的同伙与你目标不一致则视为放弃")



















ban = on_command('全禁')
@ban.handle()
async def _(bot: Bot):
        await bot.set_group_whole_ban(group_id=646017612,enable=True)

ttt = on_command('你好')
@ttt.handle()
async def _(bot: Bot,event:GroupMessageEvent):
        await bot.send_private_msg(user_id=2698595115,message="你好",auto_escape=True)