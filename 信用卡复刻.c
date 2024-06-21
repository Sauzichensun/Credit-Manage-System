#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
程序说明：
//可将本程序想像成一张可以网购的信用卡
//主要功能包括:
(1)开卡功能：
    开卡:模拟开卡功能，增加一条客户记录，每个客户至少包含姓名、身份证号、
    联系电话，消费记录(商户名称，消费金额，消费日期，终端号等)，透支额度，还款记录(日期，金额等)，
    账户余额等信息，并存入文件中;
    //开卡账户信息查看结构体了解
    //欠款金额=透支金额+透支利息，查看时不包括到查看时，距离上一次操作的这段时间
(2)购物:模拟购物过程(判断是否在透支范围内);
    //购物时，如果金额不足，会选择直接透支支付（可改进）
    //每次购物时会查看上次是否有透支记录，如果有，会直接计算距离本次购物时间，得出该时期内这笔透支金额产生的利息
(3)退款:模拟退款过程;
    //模拟某次消费的撤回（如同退货）
    //如果有透支金额，退款资金直接算在余额上，而不会弥补金额
    //每次退款，如果有透支金额，仍需记录距离上次操作时间内产生的利息，但是，由于该程序
    目前退款资金直接算在余额上，所以对透支金额不会产生影响，所以暂时不考虑
(4)计算还款额:设定记帐日(比如每月1日)，
计算客户应还款额和透支利息(自己设计计算方法);
    //本程序在查看还款额时，直接=（由每次记录的透支利息）+（由当次查看日期计算最新的透支利息）
    //查看还款额时，不累加到客户利息中，只是供客户查看到目前为止所要还款的金额
(5)还款:模拟还款过程;
    //每次还款进行记录
    //还款弥补优先级：透支金额>透支利息>余额
    //每次还款，如果有透支金额，仍需记录距离上次操作时间内产生的利息
(6)退出系统

二、实验要求
(1)贯彻结构化的程序设计思想。用户界面友好，
功能明确，操作方便。
(2)要求有退出功能，并可以适当增加其它相关功能。
(3)代码应适当缩进，并给出必要的注释，
以增强程序的可读性。
*/

/*商品名称,客户姓名最大长度
注：由于数组最后一位需要存储'\0',所以实际上只能存储19位字符*/
#define MAX_NAME_LENGTH 20
/*终端号,身份证号最大长度*/
#define MAX_ID_LENGTH 20
/*最大手机号长度*/
#define MAX_PHONE_LENGTH 20
/*最大消费记录，还款记录，客户量长度*/
#define MAX_RECORD_LENGTH 20
/*宏定义文件名*/
#define FILENAME "consumers.dat"

/*定义利率*/
#define YEAR_RATE 1
#define MONTH_RATE 1.2
#define DAY_RATE 0.05
/*消费记录*/

typedef struct
{
    /*商品名称*/
    char merchantName[MAX_NAME_LENGTH];
    /*消费金额*/
    double consumeAmount;
    /*消费日期*/
    char consumeDate[11];   /*yyyy-mm-dd*/
    /*终端号*/
    char terminalId[MAX_ID_LENGTH];
}Transaction;

/*还款记录*/
typedef struct
{
    /*还款日期*/
    char repayDate[11];    /*yyyy-mm-dd*/
    /*还款金额*/
    double repayAmount;
}Repay;

/*客户记录*/
typedef struct
{
    /*客户姓名*/
    char consumerName[MAX_NAME_LENGTH];
    /*身份证号*/
    char consumerId[MAX_ID_LENGTH];
    /*联系电话*/
    char consumerPhone[MAX_PHONE_LENGTH];
    /*客户消费记录*/
    Transaction transaction[MAX_RECORD_LENGTH];
    int transactionCount;
    /*透支额度*/
    double creditLimit;
    /*还款记录*/
    Repay repay[MAX_RECORD_LENGTH];
    int repayCount;
    /*账户余额*/
    double amountBalance;
    /*透支金额*/
    double overdraftAmount;
    /*透支利息*/
    double overdraftInterest;
    /*目前可透支金额*/
    double currentCreditLimit;
}Consumer;


void Add_Consumer();
void Output_ConsumerInfo(int count);
void Shop();
void Refund();
double Calculate_Repayment();
void Make_Repayment();
void Load_ConsumerInfo(Consumer consumers[], int *consumerCount);


int main()
{
    int choice;
    while (1)
    {
        printf("\n信用卡管理系统\n");
        printf("1. 注册账户\n");
        printf("2. 购物\n");
        printf("3. 退款\n");
        printf("4. 计算还款金额\n");
        printf("5. 还款交易\n");
        printf("6. 显示当前所有账户信息:\n");
        printf("7. 退出\n");
        printf("输入你的选择:");
        fflush(stdin);
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            Add_Consumer();
            break;
        case 2:
            Shop();
            break;
        case 3:
            Refund();
            break;
        case 4:
            printf("还款金额为:%lf\n", Calculate_Repayment());
            break;
        case 5:
            Make_Repayment();
            break;
        case 6:
            Output_ConsumerInfo(MAX_RECORD_LENGTH);
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

double Calculate_Interest(double overdraftAmount,
    char lastDate[], char currentDate[]);
void Load_ConsumerInfo(Consumer consumers[], int *consumerCount);


/*模拟开卡，并存入文件中*/
void Add_Consumer()
{
    Consumer consumer;
    FILE *file = fopen(FILENAME, "ab");
    /*文件打开失败*/
    if (!file)
    {
        fprintf(stderr, "无法打开文件\n");
        return;
    }

    printf("输入客户姓名:");
    /*读取客户姓名，使用fgets函数防止用户输入过长导致数组溢出*/
    fflush(stdin);
    fgets(consumer.consumerName, MAX_NAME_LENGTH, stdin);
    /*清空溢出时的缓冲区，防止对后续输入造成干扰*/

    printf("输入客户ID号:");
    fflush(stdin);
    fgets(consumer.consumerId, MAX_ID_LENGTH, stdin);

    printf("输入客户手机号:");
    fflush(stdin);
    fgets(consumer.consumerPhone, MAX_PHONE_LENGTH, stdin);

    printf("输入最大透支额度:");
    fflush(stdin);
    scanf("%lf", &consumer.creditLimit);

    printf("输入初始账户余额:");
    fflush(stdin);
    scanf("%lf", &consumer.amountBalance);
    /*初始化账户信息*/
    /*账户余额，还款次数，消费次数,透支金额,透支利息初始值为0*/
    consumer.repayCount = 0;
    consumer.transactionCount = 0;
    consumer.overdraftAmount = 0;
    consumer.overdraftInterest = 0;

    /*目前可透支金额=最大透支金额-已透支金额*/
    consumer.currentCreditLimit = consumer.creditLimit - consumer.overdraftAmount;
    /*将用户信息写入二进制文件*/
    fwrite(&consumer, sizeof(Consumer), 1, file);
    fclose(file);
    printf("成功开通账户!\n");
    return;
}



void Load_ConsumerInfo(Consumer consumers[], int *consumerCount)
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        fprintf(stderr, "无法打开文件\n");
        return;
    }
    while (fread(&consumers[*consumerCount], sizeof(Consumer), 1, file))
        (*consumerCount)++;

    fclose(file);
}

void trim_newline(char *str[], int count)
{
    for (int i = 0;i < count;i++)
    {
        size_t len = strlen(str[i]);
        if (len > 0 && str[i][len - 1] == '\n')
        {
            str[i][len - 1] = '\0';
        }
    }
}
void Output_ConsumerInfo(int count)
{
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumersCount = 0;
    Load_ConsumerInfo(consumers, &consumersCount);
    int i = 0;
    printf("%-10s %-18s %-15s %-10s %-15s %-15s %-12s %-10s %-10s %-10s\n",
        "姓名", "身份证号", "联系电话", "消费次数", "当前可透支额度",
        "最大透支额度", "已透支金额", "还款次数", "账户余额", "欠款金额");
    while (count > i && i < consumersCount)
    {
        char *str[] = { consumers[i].consumerId,consumers[i].consumerPhone,consumers[i].consumerName };
        trim_newline(str, 3);
        printf("%-10s %-18s %-15s %-10d %-15.2lf %-15.2lf %-12.2lf %-10d %-10.2lf %-10.2lf\n",
            consumers[i].consumerName,
            consumers[i].consumerId,
            consumers[i].consumerPhone,
            consumers[i].transactionCount,
            consumers[i].currentCreditLimit,
            consumers[i].creditLimit,
            consumers[i].overdraftAmount,
            consumers[i].repayCount,
            consumers[i].amountBalance,
            consumers[i].overdraftAmount + consumers[i].overdraftInterest);
        i++;
    }
    return;
}

/*输出消费记录*/
void Output_TransactionInfo(Consumer consumer)
{
    int i = 0;
    printf("%-10s %-18s %-15s %-10s %-15s %-15s\n",
        "姓名", "身份证号", "联系电话", "商品名称", "消费金额", "消费日期");
    for (i = 0;i < consumer.transactionCount;i++)
    {
        printf("%-10s %-18s %-15s %-10s %-10lf %-15s", consumer.consumerName,
            consumer.consumerId,
            consumer.consumerPhone,
            consumer.transaction[i].merchantName,
            consumer.transaction[i].consumeAmount,
            consumer.transaction[i].consumeDate);
    }
    return;
}

/*根据客户ID查找账户在列表中的索引值*/
int Find_Consumer(Consumer consumers[], char Id[], int consumerCount)
{
    int index = -1;
    for (int i = 0;i < consumerCount;i++)
    {
        if (strcmp(Id, consumers[i].consumerId) == 0)
        {
            index = i;
            break;
        }
    }
    return index;
}

/*更新数据库*/
void Save_Consumers(Consumer consumer[], int consumersCount)
{
    FILE *file = fopen(FILENAME, "wb");
    if (!file)
    {
        fprintf(stderr, "文件打开失败!\n");
        return;
    }
    /*将更新后的数据重新写入*/
    fwrite(consumer, sizeof(Consumer), consumersCount, file);
    fclose(file);
}

/*计算利息*/
double Calculate_Interest(double overdraftAmount,
    char lastDate[], char currentDate[])
{
    int lastYear, lastMonth, lastDay;
    int currentYear, currentMonth, currentDay;
    int yearDepositTerm, monthDepositTerm, dayDepositTerm;
    double overdraftInterest;
    sscanf(lastDate, "%d-%d-%d", &lastYear, &lastMonth, &lastDay);
    sscanf(currentDate, "%d-%d-%d", &currentYear, &currentMonth, &currentDay);
    /*计算时间差*/
    dayDepositTerm = currentDay - lastDay;
    monthDepositTerm = currentMonth - lastMonth;
    yearDepositTerm = currentYear - lastYear;

    if (dayDepositTerm < 0)
    {
        dayDepositTerm += 30;
        monthDepositTerm--;
    }
    if (monthDepositTerm < 0)
    {
        monthDepositTerm += 12;
        yearDepositTerm--;
    }
    /*这个利息为当前段的时间内的利息，并不是总利息*/
    overdraftInterest = (overdraftAmount * YEAR_RATE * yearDepositTerm) +
        (overdraftAmount * MONTH_RATE * monthDepositTerm) +
        (overdraftAmount * DAY_RATE * dayDepositTerm);
    return overdraftInterest;
}

int Compare_Date(char date1[], char date2[])
{
    int date1Year, date1Month, date1Day;
    int date2Year, date2Month, date2Day;
    sscanf(date1, "%d-%d-%d", &date1Year, &date1Month, &date1Day);
    sscanf(date1, "%d-%d-%d", &date2Year, &date2Month, &date2Day);
    if (date1Year > date2Year) return 1;
    if (date1Year < date2Year) return 2;
    if (date1Month > date2Month) return 1;
    if (date1Month < date2Month) return 2;
    if (date1Day > date2Day) return 1;
    if (date1Day < date2Day) return 2;
    return 0;
}

/*计算到目前位置最后一次消费或还款产生的利息*/
double Calculate_LastInterest(Consumer consumer, char currentDate[])
{
    /*对比最近的一次操作是消费还是还款*/
    char lastRepayDate[11], lastTransactionDate[11];
    int lastRepayDateYear, lastRepayDateMonth, lastRepayDateDay;
    int lastTransactionDateYear, lastTransactionDateMonth, lastTransactionDateDay;
    char lastDate[11];
    double interest = 0;
    int indexTransaction, indexRepay;
    indexRepay = consumer.repayCount - 1;
    indexTransaction = consumer.transactionCount - 1;
    strcpy(lastTransactionDate, consumer.transaction[consumer.transactionCount - 1].consumeDate);
    strcpy(lastRepayDate, consumer.repay[consumer.repayCount - 1].repayDate);
    /*由于可能不存在上次消费或者还款记录，多以分情况讨论*/
    if (indexTransaction != -1 && indexRepay != -1)
    {
        /*计算最近的操作是什么（消费or还款）*/
        int calculateObject = Compare_Date(lastRepayDate, lastTransactionDate);
        if (calculateObject == 0 || calculateObject == 1) strcpy(lastDate, lastRepayDate);
        if (calculateObject == 0 || calculateObject == 2) strcpy(lastDate, lastTransactionDate);
        interest = Calculate_Interest(consumer.overdraftAmount, lastDate, currentDate);
    }
    else if (indexTransaction != -1 && indexRepay == -1)
    {
        interest = Calculate_Interest(consumer.overdraftAmount, lastTransactionDate, currentDate);
    }
    else if (indexTransaction == -1 && indexRepay != -1)
    {
        interest = Calculate_Interest(consumer.overdraftAmount, lastRepayDate, currentDate);

    }
    else if (indexTransaction == -1 && indexRepay == -1)
    {
        interest = 0;
    }
    return interest;
}

/*模拟购物*/
void Shop()
{
    char Id[MAX_ID_LENGTH];
    /*获取消费用户ID*/
    printf("输入客户ID:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumerCount = 0;

    /*加载数据库数据*/
    Load_ConsumerInfo(consumers, &consumerCount);

    /*查找该消费用户在数据库中对应的索引*/
    int index = Find_Consumer(consumers, Id, consumerCount);

    if (index == -1)
    {
        printf("该用户账户信息不存在!\n");
        return;
    }
    /*获取该消费用户的消费信息*/
    Transaction transaction;
    printf("输入商品名称:");
    fflush(stdin);
    fgets(transaction.merchantName, MAX_NAME_LENGTH, stdin);

    printf("输入消费金额:");
    fflush(stdin);
    scanf("%lf", &transaction.consumeAmount);

    printf("输入消费日期:");
    fflush(stdin);
    fgets(transaction.consumeDate, 11, stdin);

    printf("输入终端号:");
    fflush(stdin);
    fgets(transaction.terminalId, MAX_ID_LENGTH, stdin);

    /*更新购买后账户余额等信息*/

    /*账户余额不足时
    暂时选择直接透支
    透支后金额为0，不为负*/
    /*透支+余额不足时*/
    if (consumers[index].amountBalance + consumers[index].currentCreditLimit < transaction.consumeAmount)
    {
        printf("账户余额不足,且目前账户最大透支额度不足!\n");
        return;
    }
    /*消费前，计算上次还款或消费后是否有透支欠款，如果有，需计算这段时间的透支利息
    透支利息=透支金额*利率*存期
    当前总欠款=透支金额+透支利息*/
    if (consumers[index].overdraftAmount > 0)
    {
        double interest = Calculate_LastInterest(consumers[index], transaction.consumeDate);
        consumers[index].overdraftInterest += interest;
    }
    /*透支+余额足够时*/
    /*更新余额*/
    consumers[index].amountBalance = consumers[index].amountBalance - transaction.consumeAmount;
    /*余额小于0代表进行了透支支付*/
    if (consumers[index].amountBalance < 0)
    {
        consumers[index].overdraftAmount -= consumers[index].amountBalance;
        consumers[index].amountBalance = 0;
        consumers[index].currentCreditLimit = consumers[index].creditLimit - consumers[index].overdraftAmount;
    }
    /*存入用户的数据项中*/
    consumers[index].transaction[consumers[index].transactionCount++] = transaction;
    /*将更新后的用户数据重新加载到数据中*/
    Save_Consumers(consumers, consumerCount);
    printf("商品交易完成!\n");
}

/*退款-目前理解为退货*/
void Refund()
{
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumersCount = 0;
    Load_ConsumerInfo(consumers, &consumersCount);

    char Id[MAX_ID_LENGTH];
    printf("输入退款客户Id:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);

    int index = Find_Consumer(consumers, Id, consumersCount);
    if (index == -1)
    {
        printf("该用户账户信息不存在!\n");
        return;
    }

    int refoundAmount = 0;
    char refoundTerminalId[MAX_ID_LENGTH];
    printf("输入退款商品的终端号:");
    fflush(stdin);
    fgets(refoundTerminalId, MAX_ID_LENGTH, stdin);

    /*查找该条最近的一条消费记录*/
    int i;
    for (i = consumers[index].transactionCount - 1;i >= 0;i--)
    {
        if (strcmp(consumers[index].transaction[i].terminalId, refoundTerminalId) == 0)
        {
            /*目前暂时不直接弥补透支金额，而是加到账户余额上*/
            consumers[index].amountBalance += consumers[index].transaction[i].consumeAmount;
            /*删除该条消费记录即覆盖数据*/
            for (int j = i + 1;j <= consumers[index].transactionCount - 1;j++)
            {
                consumers[index].transaction[j - 1] = consumers[index].transaction[j];
            }
            consumers[index].transactionCount--;
            break;
        }
    }
    if (i < 0)
    {
        printf("未找到改条商品的消费记录!\n");
        return;
    }
    else
    {
        Save_Consumers(consumers, consumersCount);
        printf("成功退款!\n");
    }

}

/*计算到目前为止应还款的数目*/
double Calculate_Repayment()
{
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumerCount = 0;
    Load_ConsumerInfo(consumers, &consumerCount);

    char Id[MAX_ID_LENGTH];
    printf("输入客户ID:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);

    int index = Find_Consumer(consumers, Id, consumerCount);
    if (index == -1)
    {
        printf("用户不存在!\n");
        return 0;
    }

    /*计算还款利息*/
    double debt = 0;
    char currentDate[11];
    printf("输入当前日期:");
    fflush(stdin);
    fgets(currentDate, 11, stdin);

    /*还款总额=目前的利息（当前段利息+以往利息）+透支总额*/
    debt = Calculate_LastInterest(consumers[index], currentDate) + consumers[index].overdraftInterest + consumers[index].overdraftAmount;
    printf("金额：%lf %lf %lf\n", debt, consumers[index].overdraftInterest, consumers[index].overdraftAmount);
    return debt;
}

void Make_Repayment()
{
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumersCount = 0;
    Load_ConsumerInfo(consumers, &consumersCount);

    char Id[MAX_ID_LENGTH];
    printf("输入客户ID:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);

    int index = Find_Consumer(consumers, Id, consumersCount);
    if (index == -1)
    {
        printf("未找到客户账户信息!\n");
        return;
    }
    if (consumers[index].overdraftAmount + consumers[index].overdraftInterest == 0)
    {
        printf("不存在还款金额!无需进行还款!\n");
        return;
    }
    Repay repayment;
    printf("输入还款金额:");
    fflush(stdin);
    scanf("%lf", &repayment.repayAmount);

    printf("输入还款日期:(yyyy-mm-dd)");
    fflush(stdin);
    fgets(repayment.repayDate, 11, stdin);

    /*更新上次操作留下的利息*/
    if (consumers[index].overdraftAmount > 0)
    {
        double interest = Calculate_LastInterest(consumers[index], repayment.repayDate);
        consumers[index].overdraftInterest += interest;
    }

    consumers[index].overdraftAmount -= repayment.repayAmount;
    consumers[index].currentCreditLimit = consumers[index].creditLimit - consumers[index].overdraftAmount;
    consumers[index].repay[consumers[index].repayCount++] = repayment;
    /*还款金额大于透支金额时，先补利息再补余额*/
    if (consumers[index].overdraftAmount < 0)
    {
        double extra = -consumers[index].overdraftAmount;
        consumers[index].overdraftAmount = 0;
        consumers[index].currentCreditLimit = consumers[index].creditLimit - consumers[index].overdraftAmount;
        if (consumers[index].overdraftInterest - extra < 0)
        {
            extra -= consumers[index].overdraftInterest;
            consumers[index].overdraftInterest = 0;
            consumers[index].amountBalance += extra;
        }
    }
    Save_Consumers(consumers, consumersCount);
    printf("还款成功!\n");
}

