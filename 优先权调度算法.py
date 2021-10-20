class Process:
    name = '未命名'  # 进程名字
    time = 0  # 要求运行时间
    priority = 0  # 优先权
    status = 'R'  # 进程状态 R为就绪 E为结束


# 进程初始化，赋值进程名、要求运行时间、优先权
def initialize(pro_group):
    for i in range(len(pro_group)):
        pro_group[i].name = 'P' + str(i + 1)  # 为进程命名P1，P2, P3, P4, P5
        pro_group[i].time = int(input("输入{}进程的要求运行时间：".format(pro_group[i].name)))
        pro_group[i].priority = int(input("输入{}进程的优先权:".format(pro_group[i].name)))
    return pro_group


# 对进程按照优先权顺序排序
def process_sort(pro_group):
    pro_group_pri = []
    for i in range(len(pro_group)):
        pro_group_pri.append(pro_group[i].priority)     # 提取所有进程的优先权,放在一个列表（pro_group_pri）中
    pro_dict = list(zip(pro_group_pri, pro_group))      # 生成一个权值和进程的数据对列表
    pro_dict = sorted(pro_dict, key=lambda d: (d[0], 5-int(d[1].name[1])), reverse=True)   # 将列表按照键优先权从大到小排序
    pro_group = []
    print("当前对列为:", end='')
    for i in pro_dict:
        pro_group.append(i[1])
        print(i[1].name, end='')
    print('   ', end='')
    return pro_group


def execute(pro_group):
    while pro_group:
        print("执行了{}进程".format(pro_group[0].name))
        pro_group[0].time -= 1
        pro_group[0].priority -= 1
        if pro_group[0].time == 0:
            pro_group[0].status = 'E'
            print("将{}进程从队列中去除".format(pro_group[0].name))
            pro_group.pop(0)
        pro_group = process_sort(pro_group)


def main():
    p1 = Process()
    p2 = Process()
    p3 = Process()
    p4 = Process()
    p5 = Process()
    pro_group = [p1, p2, p3, p4, p5]
    # 进程初始化
    initialize(pro_group)
    # 排序
    pro_group = process_sort(pro_group)
    # 执行
    execute(pro_group)


if __name__ == '__main__':
    main()
