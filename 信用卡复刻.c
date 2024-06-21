#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
����˵����
//�ɽ������������һ�ſ������������ÿ�
//��Ҫ���ܰ���:
(1)�������ܣ�
    ����:ģ�⿪�����ܣ�����һ���ͻ���¼��ÿ���ͻ����ٰ������������֤�š�
    ��ϵ�绰�����Ѽ�¼(�̻����ƣ����ѽ��������ڣ��ն˺ŵ�)��͸֧��ȣ������¼(���ڣ�����)��
    �˻�������Ϣ���������ļ���;
    //�����˻���Ϣ�鿴�ṹ���˽�
    //Ƿ����=͸֧���+͸֧��Ϣ���鿴ʱ���������鿴ʱ��������һ�β��������ʱ��
(2)����:ģ�⹺�����(�ж��Ƿ���͸֧��Χ��);
    //����ʱ��������㣬��ѡ��ֱ��͸֧֧�����ɸĽ���
    //ÿ�ι���ʱ��鿴�ϴ��Ƿ���͸֧��¼������У���ֱ�Ӽ�����뱾�ι���ʱ�䣬�ó���ʱ�������͸֧����������Ϣ
(3)�˿�:ģ���˿����;
    //ģ��ĳ�����ѵĳ��أ���ͬ�˻���
    //�����͸֧���˿��ʽ�ֱ����������ϣ��������ֲ����
    //ÿ���˿�����͸֧�������¼�����ϴβ���ʱ���ڲ�������Ϣ�����ǣ����ڸó���
    Ŀǰ�˿��ʽ�ֱ����������ϣ����Զ�͸֧�������Ӱ�죬������ʱ������
(4)���㻹���:�趨������(����ÿ��1��)��
����ͻ�Ӧ������͸֧��Ϣ(�Լ���Ƽ��㷽��);
    //�������ڲ鿴�����ʱ��ֱ��=����ÿ�μ�¼��͸֧��Ϣ��+���ɵ��β鿴���ڼ������µ�͸֧��Ϣ��
    //�鿴�����ʱ�����ۼӵ��ͻ���Ϣ�У�ֻ�ǹ��ͻ��鿴��ĿǰΪֹ��Ҫ����Ľ��
(5)����:ģ�⻹�����;
    //ÿ�λ�����м�¼
    //�����ֲ����ȼ���͸֧���>͸֧��Ϣ>���
    //ÿ�λ�������͸֧�������¼�����ϴβ���ʱ���ڲ�������Ϣ
(6)�˳�ϵͳ

����ʵ��Ҫ��
(1)�᳹�ṹ���ĳ������˼�롣�û������Ѻã�
������ȷ���������㡣
(2)Ҫ�����˳����ܣ��������ʵ�����������ع��ܡ�
(3)����Ӧ�ʵ���������������Ҫ��ע�ͣ�
����ǿ����Ŀɶ��ԡ�
*/

/*��Ʒ����,�ͻ�������󳤶�
ע�������������һλ��Ҫ�洢'\0',����ʵ����ֻ�ܴ洢19λ�ַ�*/
#define MAX_NAME_LENGTH 20
/*�ն˺�,���֤����󳤶�*/
#define MAX_ID_LENGTH 20
/*����ֻ��ų���*/
#define MAX_PHONE_LENGTH 20
/*������Ѽ�¼�������¼���ͻ�������*/
#define MAX_RECORD_LENGTH 20
/*�궨���ļ���*/
#define FILENAME "consumers.dat"

/*��������*/
#define YEAR_RATE 1
#define MONTH_RATE 1.2
#define DAY_RATE 0.05
/*���Ѽ�¼*/

typedef struct
{
    /*��Ʒ����*/
    char merchantName[MAX_NAME_LENGTH];
    /*���ѽ��*/
    double consumeAmount;
    /*��������*/
    char consumeDate[11];   /*yyyy-mm-dd*/
    /*�ն˺�*/
    char terminalId[MAX_ID_LENGTH];
}Transaction;

/*�����¼*/
typedef struct
{
    /*��������*/
    char repayDate[11];    /*yyyy-mm-dd*/
    /*������*/
    double repayAmount;
}Repay;

/*�ͻ���¼*/
typedef struct
{
    /*�ͻ�����*/
    char consumerName[MAX_NAME_LENGTH];
    /*���֤��*/
    char consumerId[MAX_ID_LENGTH];
    /*��ϵ�绰*/
    char consumerPhone[MAX_PHONE_LENGTH];
    /*�ͻ����Ѽ�¼*/
    Transaction transaction[MAX_RECORD_LENGTH];
    int transactionCount;
    /*͸֧���*/
    double creditLimit;
    /*�����¼*/
    Repay repay[MAX_RECORD_LENGTH];
    int repayCount;
    /*�˻����*/
    double amountBalance;
    /*͸֧���*/
    double overdraftAmount;
    /*͸֧��Ϣ*/
    double overdraftInterest;
    /*Ŀǰ��͸֧���*/
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
        printf("\n���ÿ�����ϵͳ\n");
        printf("1. ע���˻�\n");
        printf("2. ����\n");
        printf("3. �˿�\n");
        printf("4. ���㻹����\n");
        printf("5. �����\n");
        printf("6. ��ʾ��ǰ�����˻���Ϣ:\n");
        printf("7. �˳�\n");
        printf("�������ѡ��:");
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
            printf("������Ϊ:%lf\n", Calculate_Repayment());
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


/*ģ�⿪�����������ļ���*/
void Add_Consumer()
{
    Consumer consumer;
    FILE *file = fopen(FILENAME, "ab");
    /*�ļ���ʧ��*/
    if (!file)
    {
        fprintf(stderr, "�޷����ļ�\n");
        return;
    }

    printf("����ͻ�����:");
    /*��ȡ�ͻ�������ʹ��fgets������ֹ�û�������������������*/
    fflush(stdin);
    fgets(consumer.consumerName, MAX_NAME_LENGTH, stdin);
    /*������ʱ�Ļ���������ֹ�Ժ���������ɸ���*/

    printf("����ͻ�ID��:");
    fflush(stdin);
    fgets(consumer.consumerId, MAX_ID_LENGTH, stdin);

    printf("����ͻ��ֻ���:");
    fflush(stdin);
    fgets(consumer.consumerPhone, MAX_PHONE_LENGTH, stdin);

    printf("�������͸֧���:");
    fflush(stdin);
    scanf("%lf", &consumer.creditLimit);

    printf("�����ʼ�˻����:");
    fflush(stdin);
    scanf("%lf", &consumer.amountBalance);
    /*��ʼ���˻���Ϣ*/
    /*�˻���������������Ѵ���,͸֧���,͸֧��Ϣ��ʼֵΪ0*/
    consumer.repayCount = 0;
    consumer.transactionCount = 0;
    consumer.overdraftAmount = 0;
    consumer.overdraftInterest = 0;

    /*Ŀǰ��͸֧���=���͸֧���-��͸֧���*/
    consumer.currentCreditLimit = consumer.creditLimit - consumer.overdraftAmount;
    /*���û���Ϣд��������ļ�*/
    fwrite(&consumer, sizeof(Consumer), 1, file);
    fclose(file);
    printf("�ɹ���ͨ�˻�!\n");
    return;
}



void Load_ConsumerInfo(Consumer consumers[], int *consumerCount)
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        fprintf(stderr, "�޷����ļ�\n");
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
        "����", "���֤��", "��ϵ�绰", "���Ѵ���", "��ǰ��͸֧���",
        "���͸֧���", "��͸֧���", "�������", "�˻����", "Ƿ����");
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

/*������Ѽ�¼*/
void Output_TransactionInfo(Consumer consumer)
{
    int i = 0;
    printf("%-10s %-18s %-15s %-10s %-15s %-15s\n",
        "����", "���֤��", "��ϵ�绰", "��Ʒ����", "���ѽ��", "��������");
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

/*���ݿͻ�ID�����˻����б��е�����ֵ*/
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

/*�������ݿ�*/
void Save_Consumers(Consumer consumer[], int consumersCount)
{
    FILE *file = fopen(FILENAME, "wb");
    if (!file)
    {
        fprintf(stderr, "�ļ���ʧ��!\n");
        return;
    }
    /*�����º����������д��*/
    fwrite(consumer, sizeof(Consumer), consumersCount, file);
    fclose(file);
}

/*������Ϣ*/
double Calculate_Interest(double overdraftAmount,
    char lastDate[], char currentDate[])
{
    int lastYear, lastMonth, lastDay;
    int currentYear, currentMonth, currentDay;
    int yearDepositTerm, monthDepositTerm, dayDepositTerm;
    double overdraftInterest;
    sscanf(lastDate, "%d-%d-%d", &lastYear, &lastMonth, &lastDay);
    sscanf(currentDate, "%d-%d-%d", &currentYear, &currentMonth, &currentDay);
    /*����ʱ���*/
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
    /*�����ϢΪ��ǰ�ε�ʱ���ڵ���Ϣ������������Ϣ*/
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

/*���㵽Ŀǰλ�����һ�����ѻ򻹿��������Ϣ*/
double Calculate_LastInterest(Consumer consumer, char currentDate[])
{
    /*�Ա������һ�β��������ѻ��ǻ���*/
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
    /*���ڿ��ܲ������ϴ����ѻ��߻����¼�����Է��������*/
    if (indexTransaction != -1 && indexRepay != -1)
    {
        /*��������Ĳ�����ʲô������or���*/
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

/*ģ�⹺��*/
void Shop()
{
    char Id[MAX_ID_LENGTH];
    /*��ȡ�����û�ID*/
    printf("����ͻ�ID:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumerCount = 0;

    /*�������ݿ�����*/
    Load_ConsumerInfo(consumers, &consumerCount);

    /*���Ҹ������û������ݿ��ж�Ӧ������*/
    int index = Find_Consumer(consumers, Id, consumerCount);

    if (index == -1)
    {
        printf("���û��˻���Ϣ������!\n");
        return;
    }
    /*��ȡ�������û���������Ϣ*/
    Transaction transaction;
    printf("������Ʒ����:");
    fflush(stdin);
    fgets(transaction.merchantName, MAX_NAME_LENGTH, stdin);

    printf("�������ѽ��:");
    fflush(stdin);
    scanf("%lf", &transaction.consumeAmount);

    printf("������������:");
    fflush(stdin);
    fgets(transaction.consumeDate, 11, stdin);

    printf("�����ն˺�:");
    fflush(stdin);
    fgets(transaction.terminalId, MAX_ID_LENGTH, stdin);

    /*���¹�����˻�������Ϣ*/

    /*�˻�����ʱ
    ��ʱѡ��ֱ��͸֧
    ͸֧����Ϊ0����Ϊ��*/
    /*͸֧+����ʱ*/
    if (consumers[index].amountBalance + consumers[index].currentCreditLimit < transaction.consumeAmount)
    {
        printf("�˻�����,��Ŀǰ�˻����͸֧��Ȳ���!\n");
        return;
    }
    /*����ǰ�������ϴλ�������Ѻ��Ƿ���͸֧Ƿ�����У���������ʱ���͸֧��Ϣ
    ͸֧��Ϣ=͸֧���*����*����
    ��ǰ��Ƿ��=͸֧���+͸֧��Ϣ*/
    if (consumers[index].overdraftAmount > 0)
    {
        double interest = Calculate_LastInterest(consumers[index], transaction.consumeDate);
        consumers[index].overdraftInterest += interest;
    }
    /*͸֧+����㹻ʱ*/
    /*�������*/
    consumers[index].amountBalance = consumers[index].amountBalance - transaction.consumeAmount;
    /*���С��0���������͸֧֧��*/
    if (consumers[index].amountBalance < 0)
    {
        consumers[index].overdraftAmount -= consumers[index].amountBalance;
        consumers[index].amountBalance = 0;
        consumers[index].currentCreditLimit = consumers[index].creditLimit - consumers[index].overdraftAmount;
    }
    /*�����û�����������*/
    consumers[index].transaction[consumers[index].transactionCount++] = transaction;
    /*�����º���û��������¼��ص�������*/
    Save_Consumers(consumers, consumerCount);
    printf("��Ʒ�������!\n");
}

/*�˿�-Ŀǰ���Ϊ�˻�*/
void Refund()
{
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumersCount = 0;
    Load_ConsumerInfo(consumers, &consumersCount);

    char Id[MAX_ID_LENGTH];
    printf("�����˿�ͻ�Id:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);

    int index = Find_Consumer(consumers, Id, consumersCount);
    if (index == -1)
    {
        printf("���û��˻���Ϣ������!\n");
        return;
    }

    int refoundAmount = 0;
    char refoundTerminalId[MAX_ID_LENGTH];
    printf("�����˿���Ʒ���ն˺�:");
    fflush(stdin);
    fgets(refoundTerminalId, MAX_ID_LENGTH, stdin);

    /*���Ҹ��������һ�����Ѽ�¼*/
    int i;
    for (i = consumers[index].transactionCount - 1;i >= 0;i--)
    {
        if (strcmp(consumers[index].transaction[i].terminalId, refoundTerminalId) == 0)
        {
            /*Ŀǰ��ʱ��ֱ���ֲ�͸֧�����Ǽӵ��˻������*/
            consumers[index].amountBalance += consumers[index].transaction[i].consumeAmount;
            /*ɾ���������Ѽ�¼����������*/
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
        printf("δ�ҵ�������Ʒ�����Ѽ�¼!\n");
        return;
    }
    else
    {
        Save_Consumers(consumers, consumersCount);
        printf("�ɹ��˿�!\n");
    }

}

/*���㵽ĿǰΪֹӦ�������Ŀ*/
double Calculate_Repayment()
{
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumerCount = 0;
    Load_ConsumerInfo(consumers, &consumerCount);

    char Id[MAX_ID_LENGTH];
    printf("����ͻ�ID:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);

    int index = Find_Consumer(consumers, Id, consumerCount);
    if (index == -1)
    {
        printf("�û�������!\n");
        return 0;
    }

    /*���㻹����Ϣ*/
    double debt = 0;
    char currentDate[11];
    printf("���뵱ǰ����:");
    fflush(stdin);
    fgets(currentDate, 11, stdin);

    /*�����ܶ�=Ŀǰ����Ϣ����ǰ����Ϣ+������Ϣ��+͸֧�ܶ�*/
    debt = Calculate_LastInterest(consumers[index], currentDate) + consumers[index].overdraftInterest + consumers[index].overdraftAmount;
    printf("��%lf %lf %lf\n", debt, consumers[index].overdraftInterest, consumers[index].overdraftAmount);
    return debt;
}

void Make_Repayment()
{
    Consumer consumers[MAX_RECORD_LENGTH];
    int consumersCount = 0;
    Load_ConsumerInfo(consumers, &consumersCount);

    char Id[MAX_ID_LENGTH];
    printf("����ͻ�ID:");
    fflush(stdin);
    fgets(Id, MAX_ID_LENGTH, stdin);

    int index = Find_Consumer(consumers, Id, consumersCount);
    if (index == -1)
    {
        printf("δ�ҵ��ͻ��˻���Ϣ!\n");
        return;
    }
    if (consumers[index].overdraftAmount + consumers[index].overdraftInterest == 0)
    {
        printf("�����ڻ�����!������л���!\n");
        return;
    }
    Repay repayment;
    printf("���뻹����:");
    fflush(stdin);
    scanf("%lf", &repayment.repayAmount);

    printf("���뻹������:(yyyy-mm-dd)");
    fflush(stdin);
    fgets(repayment.repayDate, 11, stdin);

    /*�����ϴβ������µ���Ϣ*/
    if (consumers[index].overdraftAmount > 0)
    {
        double interest = Calculate_LastInterest(consumers[index], repayment.repayDate);
        consumers[index].overdraftInterest += interest;
    }

    consumers[index].overdraftAmount -= repayment.repayAmount;
    consumers[index].currentCreditLimit = consumers[index].creditLimit - consumers[index].overdraftAmount;
    consumers[index].repay[consumers[index].repayCount++] = repayment;
    /*���������͸֧���ʱ���Ȳ���Ϣ�ٲ����*/
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
    printf("����ɹ�!\n");
}

