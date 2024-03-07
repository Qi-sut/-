#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER 20
typedef struct {		//选民
	int user_number;		//选民编号
	char username[20];
	long long phonenumber;
	int vote_number;	//持有票数
}voter;
voter voters_database[MAX_NUMBER] = { 0 };
typedef struct {		//竞选者
	long long telephone_number;
	char candidate_name[20];
	long candidate_number;
	int num_of_votes;	//获得的票数
}candidate;
candidate candidates_database[MAX_NUMBER] = { 0 };
typedef struct {
	int year;
	int month;
	int day;
}date;
date originally_date = { 2024, 2, 26 };
int administrator_login_system(int* vote_ptr, int* num_ptr, int* fla, int* num_candidate_pt, int* pub_ptr);
void admin_menu(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla);
void init(int* fla, int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr);
void present_voters_information(int* vote_ptr, int* num_ptr);
void present_candidates_information(int* num_candidate_ptr);
int modify_votes_number(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla);
date modify_time(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla);
void vote(int* num_ptr, int* num_candidate_ptr, int* count_ptr, int* pub_ptr, int* fla, int* vote_ptr);
int statistical_results(int* num_candidate_ptr, int* pub_ptr);
void voters_login_system(int* num_ptr, int* vote_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla);
void candidates_login_system(int* num_candidate_ptr, int* pub_ptr, int* vote_ptr, int* num_ptr, int* fla);
void voters_menu(int* num_candidate_ptr, int* count_ptr, int* num_ptr, int* pub_ptr, int* fla, int* vote_ptr);
void  candidates_menu(int* num_candidate_ptr, int* count_ptr, int* pub_ptr, int* fla, int* vote_ptr, int* num_ptr);
int see_result(int* pub_ptr, int* num_candidate_ptr);

int main(void) {
	int flag = 0;
	int* fla = &flag;
	int vote_number = 1;		//初始票数为1
	int* vote_ptr = &vote_number;
	int current_people = 0;		//程序刚开始时选民和竞选者人数都为0
	int* num_ptr = &current_people;
	int current_candidate_people = 0;
	int* num_candidate_ptr = &current_candidate_people;
	int publish = 0;			//投票结果是否发布及更新
	int* pub_ptr = &publish;

	while (!flag) {
		init(fla, vote_ptr, num_ptr, num_candidate_ptr,pub_ptr);
	}

	return 0;
}
/*主菜单（选择身份）*/
void init(int* fla, int* vote_ptr, int* num_ptr, int*num_candidate_ptr, int* pub_ptr) {

	while (!*fla) {
		system("cls");
		printf("欢迎进入投票系统！\n\n");
		printf("请选择你的身份！\n");
		printf("1：管理员\n2：竞选者\n3：选民\n4：退出\n\n");
		printf("请输入选项前的数字：");

		char identity[MAX_NUMBER] = { 0 };
		gets_s(identity, sizeof(identity));

		if (identity[1] == 0) {		//检查是否输入‘1’‘2’‘3’‘4’之外的数据以及是否输入了多个数据
			switch (identity[0]) {
			case '1': administrator_login_system(vote_ptr, num_ptr, fla, num_candidate_ptr, pub_ptr); break;
			case '2': candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla); break;
			case '3': voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla); break;
			case '4': *fla = 1;
				return;
				break;
			default: printf("请重新输入！");
				system("pause");
				init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr);
				break;
			}
		}
		else {
			printf("请重新输入！");
			system("pause");
			init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr);
		}

	}

	

}
/*管理员登陆*/
int administrator_login_system(int* vote_ptr, int* num_ptr, int* fla, int*num_candidate_ptr, int* pub_ptr)
{
	/*先创建一个文件存入管理员的账户名及账户密码，然后提示用户让用户输入账户名及密码。
读取文件内容与输入信息进行比对若一致则登陆成功*/

	system("cls");
	FILE* first_stream = NULL;
	/*以’w‘模式打开文件若文件不存在则创建一个新文件
	  若操作成功返回0，且文件指针指向该文件*/
	errno_t err_first = fopen_s(&first_stream, "C:\\Users\\22499\\Desktop\\Administrator_login_information.txt", "w");
	if (err_first != 0 || first_stream == NULL) {
		perror("Error writing file!");
		return EXIT_FAILURE;
	}
	int error_first = fprintf_s(first_stream, "管理员");		//存入账户名若成功返回1

	fclose(first_stream);								//关闭该文件

	FILE* second_stream = NULL;
	/*以’a‘模式打开文件*/
	errno_t err_second = fopen_s(&second_stream, "C:\\Users\\22499\\Desktop\\Administrator_login_information.txt", "a");
	if (err_second != 0 || second_stream == NULL) {
		perror("Error appending file!");
		return EXIT_FAILURE;
	}

	int error_second = fprintf_s(second_stream, "\n123456789");			//追加账户密码若成功返回1

	fclose(second_stream);
	/*检查信息是否存储成功*/
	if (error_first && error_second) {
		printf("系统初始化成功！\n");
	}

	FILE* stream = NULL;
	/*打开文件读取文件内容*/
	errno_t err = fopen_s(&stream, "C:\\Users\\22499\\Desktop\\administrator_login_information.txt", "r");
	if (err != 0 || stream == NULL) {
		perror("Error opening file!");
		return EXIT_FAILURE;
	}
	char buffer[20] = { 0 };
	fscanf_s(stream, "%s", buffer, (unsigned)_countof(buffer));		//读取文件中的管理员名称
	long sum = 0;
	fscanf_s(stream, "%ld", &sum);				//读取文件中的管理员密码

	fclose(stream);								//关闭文件

	printf("请输入管理员账号名称\n");
	char administrator[20] = { 0 };
	scanf_s("%s", administrator, (unsigned)_countof(administrator));	//输入管理员名称

	/*清除缓冲区内的内容*/
	scanf_s("%*[^\n]");
	scanf_s("%*c");

	printf("请输入管理员密码（仅由数字组成）\n");
	long pas = 0;
	scanf_s("%ld", &pas);				//输入管理员密码

	scanf_s("%*[^\n]");
	scanf_s("%*c");

	/*比对输入的信息与文件中的信息是否一致*/
	if ((strcmp(buffer, administrator) == 0) && pas == sum) {
		admin_menu(vote_ptr, num_ptr, num_candidate_ptr,pub_ptr, fla);
		return 0;
	}
	else {
		printf("登陆失败！\n");
		system("pause");
		init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr);
		return 1;
	}

}
/*以管理员身份登陆成功后的菜单*/
void admin_menu(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla) {
	int flag = 0;

	
		while (!flag) {
			while (!*fla) {
			system("cls");

			printf("欢迎管理员登陆投票系统！\n");
			printf("请选择你要进行的操作：\n");
			printf("1：查看竞选者信息\n2：查看选民信息\n");
			printf("3：修改选民每天可投票数\n4：修改选举时间\n");
			printf("5：公布投票结果\n6：退出\n");
			printf("请输入选项前的数字：");

			char fuction[MAX_NUMBER] = { 0 };
			gets_s(fuction, sizeof(fuction));
			/*检查是否输入‘1’‘2’‘3’‘4’’5‘之外的数据以及是否输入了多个数据*/
			if (fuction[1] == 0) {
				switch (fuction[0])
				{
				case '1': present_candidates_information(num_candidate_ptr); break;
				case '2': present_voters_information(vote_ptr, num_ptr); break;
				case '3': *vote_ptr = modify_votes_number(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla); break;
				case '4': originally_date = modify_time(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla); break;
				case '5': statistical_results(num_candidate_ptr, pub_ptr); break;
				case '6':
					init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr);
					flag = 1;
					break;
				default: printf("请重新输入！");
					system("pause");
					admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
					break;
				}
			}
			else {
				printf("请重新输入！");
				system("pause");
				admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
			}
		}
			flag = 1;
	  }
	}
/*修改选民持有的票数*/
int modify_votes_number(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla) {
	printf("你正在尝试修改选民每天可投票数！\n");
	printf("现在，选民每天可投 %d 票\n", *vote_ptr);
	printf("你想要修改它吗？(y/n)\n");	//询问是否要进行修改
	char buffer[MAX_NUMBER] = { 0 };
	gets_s(buffer, sizeof(buffer));
	int changed_number = 0;

	if (buffer[1] == 0) {
		switch (buffer[0])
		{
		case 'y': 	printf("请输入你想要改成的票数（票数不能为零）\n");

			scanf_s("%d", &changed_number);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (changed_number == 0) {
				printf("修改失败！");
				system("pause");
				return *vote_ptr;
			}

			int change = changed_number - *vote_ptr;			//计算修改后与修改前票数差值

			for (int i = 0; i < *num_ptr; i++) {				//更新选民票数
				voters_database[i].vote_number = voters_database[i].vote_number + change;
			}



			if (changed_number != *vote_ptr) {		//检查修改前后可投票数是否相同
				printf("修改成功！");
				system("pause");
				return changed_number;
			}
			else {
				printf("你输入的票数与选民原本可投票数相等！\n");
				system("pause");
				return *vote_ptr;
			}

			break;

		case 'n': admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla); 
			return 1;
			break;
		default: printf("请重新输入！");
			system("pause");
			modify_votes_number(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
			return 1;
			break;
		}
	}
	else {
		printf("请重新输入！");
		system("pause");
		modify_votes_number(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
		return 1;
	}
}
/*修改选举时间*/
date modify_time(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla) {
	printf("你正在尝试修改选举时间！\n");
	printf("现在，选举时间为 %d/%d/%d\n", originally_date.year, originally_date.month, originally_date.day);
	printf("你是否要修改它？(y/n)\n");		//询问是否要进行修改
	char buffer[MAX_NUMBER] = { 0 };
	gets_s(buffer, sizeof(buffer));
	date temp_date = { 0 };

	if (buffer[1] == 0) {
		switch (buffer[0])
		{
		case 'y': 	printf("请输入你想要修改为的日期：（请用\" / \"将年、月、日分开）:\n");

			scanf_s("%d/%d/%d", &temp_date.year, &temp_date.month, &temp_date.day);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			break;

		case 'n': admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla); break;
		default: printf("请重新输入！");
			system("pause");
			modify_time(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
			break;
		}
	}
	else {
		printf("请重新输入！");
		system("pause");
		modify_time(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
	}

	/*如果输入不是数字或未按格式输入将导致数据为零，用于检查是否成功修改*/
	if (temp_date.year == 0 || temp_date.month == 0 || temp_date.day == 0) {
		printf("修改失败！");
		system("pause");
		return originally_date;
	}


	if (originally_date.year == temp_date.year && originally_date.month == temp_date.month && originally_date.day == temp_date.day) {
		printf("修改后的日期与原日期相同！\n");
		system("pause");
		return originally_date;
	}
	else {
		printf("修改成功！");
		system("pause");
		return temp_date;
	}
}
/*选民投票*/
void vote(int* num_ptr, int* num_candidate_ptr, int* count_ptr, int* pub_ptr, int* fla, int* vote_ptr) {

	if (*num_candidate_ptr != 0) {
		/*检查选民投票次数是否用光*/
		if (voters_database[*count_ptr].vote_number <= 0) {		//投票次数用光
			printf("你今天的投票次数已经用光了！\n");
			system("pause");
			voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
		}
		else {
			present_candidates_information(num_candidate_ptr);

			printf("这次选举将在：%d/%d/%d 举行！\n", originally_date.year, originally_date.month, originally_date.day);
			printf("请输入你想支持的竞选者的编号：");

			int buffer = 0;
			scanf_s("%d", &buffer);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (buffer != 0 && buffer <= *num_candidate_ptr) {		//检查是否正确输入了竞选者的编号
				(candidates_database[buffer - 1].num_of_votes)++;		//被投票的竞选者票数加一
				(voters_database[*count_ptr].vote_number)--;				//选民投票次数减一
				*pub_ptr = 0;

				printf("投票成功！");
				system("pause");
			}
			else {
				printf("请重新输入！");
				system("pause");
				vote(num_ptr, num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr);
			}
		}
	}
	else {
		printf("没有竞选者！\n");
		system("pause");
		voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
	}
	
}
/*发布投票结果*/
int statistical_results(int* num_candidate_ptr, int* pub_ptr) {

	if (*num_candidate_ptr != 0) {
		candidate tem[MAX_NUMBER] = { 0 };
		for (int k = 0; k < *num_candidate_ptr; k++) {
			tem[k] = candidates_database[k];
		}

		/*从大到小排序*/
		for (int i = 0; i < *num_candidate_ptr; i++) {
			candidate temp = { 0 };
			temp = tem[i];
			for (int j = i + 1; j < *num_candidate_ptr; j++) {
				if (temp.num_of_votes < tem[j].num_of_votes) {
					temp = tem[j];
					tem[j] = tem[i];
					tem[i] = temp;
				}
			}

		}

		/*先以‘w’模式打开或创建一个文件并写入第一位竞选者的信息*/
		FILE* result_stream = NULL;
		errno_t err = fopen_s(&result_stream, "C:\\Users\\22499\\Desktop\\result.txt", "w");
		if (err != 0 || result_stream == NULL) {
			perror("Opening failed!");
			return EXIT_FAILURE;
			system("pause");
		}
		fprintf_s(result_stream, "%d %s %d\n", tem[0].candidate_number, tem[0].candidate_name, tem[0].num_of_votes);

		fclose(result_stream);

		/*以‘a’模式打开文件并追加剩余竞选者的信息*/
		errno_t err_two = fopen_s(&result_stream, "C:\\Users\\22499\\Desktop\\result.txt", "a");
		if (err_two != 0 || result_stream == NULL) {
			perror("Add failed!");
			return EXIT_FAILURE;
			system("pause");
		}
		for (int i = 1; i < *num_candidate_ptr; i++) {
			fprintf_s(result_stream, "%d %s %d\n", tem[i].candidate_number, tem[i].candidate_name, tem[i].num_of_votes);
		}
		fclose(result_stream);

		if (err == 0 && err_two == 0) {
			*pub_ptr = 1;
			printf("选举结果已经成功发布！\n");
			system("pause");
			return 0;
		}
		else {
			printf("发布失败！");
			system("pause");
			return 1;
		}
	}
	else {
		printf("没有数据可供发布！\n");
		system("pause");
		return 0;
	}

}
/*选民or竞选者查看投票结果*/
int see_result(int* pub_ptr, int* num_candidate_ptr) {
	if (*pub_ptr) {
		/*以‘a’模式打开文件并格式化读取信息*/
		FILE* read_stream = NULL;
		errno_t err = fopen_s(&read_stream, "C:\\Users\\22499\\Desktop\\result.txt", "r");
		if (err != 0 || read_stream == NULL) {
			perror("Failed read!");
			return EXIT_FAILURE;
		}
		candidate temp = { 0 };

		printf("投票结果如下：\n");
		printf("编号 竞选者姓名 获得票数\n");
		for (int i = 0; i < *num_candidate_ptr; i++) {
			fscanf_s(read_stream, "%d %s %d", &temp.candidate_number, &temp.candidate_name, MAX_NUMBER, &temp.num_of_votes);
			printf("%4d %s %10d\n", temp.candidate_number, temp.candidate_name, temp.num_of_votes);
		}

		fclose(read_stream);

		int all_vote = 0;
		for (int i = 0; i < *num_candidate_ptr; i++) {
			all_vote += candidates_database[i].num_of_votes;
		}

		printf("竞选者获得票数占比如下：\n");
		printf("竞选者名称  竞选者票数占比\n");
		for (int i = 0; i < *num_candidate_ptr; i++) {
			printf("%s %15.f%%\n", candidates_database[i].candidate_name, ((candidates_database[i].num_of_votes + 0.0) / all_vote) * 100);
		}

		system("pause");
		return 0;
	}
	else {
		printf("投票结果尚未发布或发布信息尚未更新！");
		system("pause");
		return 1;
	}
}

/*显示选民信息*/
void present_voters_information(int* vote_ptr, int* num_ptr)
{

	if ((*num_ptr) == 0)     //检查是否有选民进行了注册 
	{
		printf("没有选民信息");

		system("pause");

	}
	else
	{
		system("cls");
		printf("选民信息如下:\n");
		printf("username\tphonenumber\n");



		int count = 0;
		while (count < *num_ptr)
		{
			printf("%s %10zd\n", voters_database[count].username, voters_database[count].phonenumber);
			count++;
		}

		system("pause");
	}


}
/*显示竞选者的信息*/
void present_candidates_information(int* num_candidate_ptr)
{

	if (*num_candidate_ptr == 0)     //检查是否有竞选者进行了注册 
	{
		printf("没有竞选者信息");

		system("pause");

	}
	else
	{
		system("cls");
		printf("竞选者信息如下:\n");
		printf("number\tname\tphonenumber\t\n");

		int count = 0;
		while (count < *num_candidate_ptr)
		{
			printf("%2d %10s %10zd\n", candidates_database[count].candidate_number, candidates_database[count].candidate_name, candidates_database[count].telephone_number);
			count++;
		}

		system("pause");
	}

}
/*选民注册*/
void voters_login_system(int* num_ptr, int* vote_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla)
{
	system("cls");

	printf("请问您是否已经注册了选民账户？(y/n)\n");     //判断选民之前是否注册过账户 y代表yes n代表no
	char ch;
	scanf_s("%c", &ch, 1);

	switch (ch)
	{
	case 'y':
	{
		printf("请输入您的用户名：\n");
		char temp_name[MAX_NUMBER] = { 0 };
		scanf_s("%s", temp_name, MAX_NUMBER);

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		int flag = 0;
		int count = 0;
		for (int i = 0; i < *num_ptr && !flag; i++)
		{
			if (!strcmp(temp_name, voters_database[i].username))     //判断用户名是否存在 
			{
				flag = 1;
				count = i;
			}
		}

		if (flag) {          //用户名存在 继续输入手机号
			printf("请输入您的手机号码：\n");
			long long temp_num = 0;
			scanf_s("%zd", &temp_num);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (temp_num == voters_database[count].phonenumber)     //信息匹配 登录成功      
			{
				printf("登陆成功！");
				system("pause");

				int* count_ptr = &count;

				voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);      //进入选民菜单
			}
			else                              //信息不匹配 登录失败 
			{
				printf("信息不匹配，登陆失败！");
				system("pause");
				voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);     //进入选民注册系统
			}
		}
		else {                    //用户名不存在
			printf("该用户不存在！\n");
			system("pause");
			voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
		}

	} break;
	case 'n':
	{                                         //判断选民人数是否已满
		if (*num_ptr == MAX_NUMBER)          //选民人数已满
		{
			printf("人数已满");
			system("pause");
			voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
		}
		printf("--------------------\n");
		printf("欢迎进入选民注册系统\n");     //选民人数未满 进入选民注册系统
		printf("--------------------\n");
		int a = 0;
		long long new_telephone_number = 0;
		printf("请输入手机号以注册成为选民：");
		scanf_s("%zd", &new_telephone_number);
		for (a = 0; a < *num_ptr; ++a)     //判断所输入的手机号是否注册过
			if (voters_database[a].phonenumber == new_telephone_number)     //手机号已注册   
			{
				printf("该手机号已注册");
				system("pause");
				voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
			}
		voters_database[a].phonenumber = new_telephone_number;//手机号未注册 存入该手机号
		printf("请输入手机号拥有者的姓名：");
		scanf_s("%s", voters_database[a].username, MAX_NUMBER);
		++(*num_ptr);
		voters_database[a].user_number = *num_ptr;
		voters_database[a].vote_number = *vote_ptr;
		printf("选民注册成功\n");

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		system("pause");
		init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr); break;
	}
	default:
		printf("请重新输入！");
		voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
		break;
	}
}
/*竞选者注册*/
void candidates_login_system(int* num_candidate_ptr, int* pub_ptr, int* vote_ptr, int* num_ptr, int* fla)
{
	system("cls");

	printf("请问您是否已经注册了竞选者账户？(y/n)\n");     //判断使用者是否已经注册过账号 y代表yes n代表no
	char ch;
	scanf_s("%c", &ch, 1);

	switch (ch)
	{
	case 'y':
	{
		printf("请输入您的用户名：\n");
		char temp_name[MAX_NUMBER] = { 0 };
		scanf_s("%s", temp_name, MAX_NUMBER);

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		int flag = 0;
		int count = 0;
		for (int i = 0; i < *num_candidate_ptr && !flag; i++)
		{
			if (!strcmp(temp_name, candidates_database[i].candidate_name))     //判断用户名是否存在 
			{
				flag = 1;
				count = i;
			}
		}

		if (flag)                    //用户名存在 继续输入手机号 
		{
			printf("请输入您的手机号码：\n");
			long long temp_num = 0;
			scanf_s("%zd", &temp_num);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (temp_num == candidates_database[count].telephone_number)     //信息匹配 登录成功 
			{
				printf("登陆成功！");
				system("pause");

				int* count_ptr = &count;

				candidates_menu(num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr, num_ptr);     //进入参选者菜单

			}
			else                              //信息不匹配 登录失败 
			{
				printf("信息不匹配，登录失败");
				system("pause");
				candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);     //进入参选者注册系统
			}
		}
		else                    //用户名不存在 
		{
			printf("该用户不存在！\n");
			system("pause");
			candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);
		}

	} break;
	case 'n':
	{                    //判断参选者人数是否已满
		if (*num_candidate_ptr == MAX_NUMBER)          //参选者人数已满
		{
			printf("人数已满");
			return;
		}
		printf("------------------------\n");
		printf("欢迎进入竞选者注册系统\n");          //参选者人数未满 进入参选对象注册系统
		printf("------------------------\n");
		int a = 0;
		long long new_telephone_number = 0;
		printf("请输入手机号以注册成为竞选者：");
		scanf_s("%zd", &new_telephone_number);

		for (a = 0; a < *num_candidate_ptr; ++a)     //判断所输入的手机号是否注册过
			if (candidates_database[a].telephone_number == new_telephone_number)     //手机号已注册
			{
				printf("该手机号已注册");
				system("pause");
				candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);
			}
		candidates_database[a].telephone_number = new_telephone_number;//手机号未注册 存入该手机号
		printf("请输入手机号拥有者的姓名：");
		scanf_s("%s", candidates_database[a].candidate_name, MAX_NUMBER);
		++(*num_candidate_ptr);
		candidates_database[a].candidate_number = *num_candidate_ptr;
		candidates_database[a].num_of_votes = 0;
		printf("竞选者注册成功\n");
		*pub_ptr = 0;

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		system("pause");
		init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr); break;
	}
	default:
		printf("请重新输入！");
		system("pause");
		candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);
		break;
	}
}
/*选民菜单*/
void voters_menu(int* num_candidate_ptr, int* count_ptr, int* num_ptr, int* pub_ptr, int* fla, int* vote_ptr)
{
	while (!*fla) {
		system("cls");

		printf("欢迎%s进入投票系统！\n", voters_database[*count_ptr].username);
		printf("请选择您想要进行的操作（输入选项前的序号即可）:\n");
		printf("1:查看竞选者信息\n2:投票\n3:查看投票结果\n4:退出\n");

		int fuc = 0;
		scanf_s("%d", &fuc);

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		switch (fuc)
		{
		case 1:
			present_candidates_information(num_candidate_ptr);
			voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
			break;
		case 2:
			vote(num_ptr, num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr);
			voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
			break;
		case 3:
			see_result(pub_ptr, num_candidate_ptr);
			voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
		case 4:
			init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr); break;
		default: printf("请重新输入！");
			voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
			break;
		}
	}

	
}
/*竞选者菜单*/
void  candidates_menu(int* num_candidate_ptr, int* count_ptr, int* pub_ptr, int* fla, int*vote_ptr, int* num_ptr)
{
	while (!*fla) {

		system("cls");

		printf("欢迎进入竞选者菜单！\n");
		printf("请选择您想要进行的操作(输入选项前的序号即可）：\n");
		printf("1:查看竞选者信息\n2:查看当前投票信息汇总\n3:退出\n");

		int fuc = 0;
		scanf_s("%d", &fuc);

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		switch (fuc)
		{
		case 1:
			present_candidates_information(num_candidate_ptr);
			candidates_menu(num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr, num_ptr);
			break;
		case 2:
			see_result(pub_ptr, num_candidate_ptr);
			candidates_menu(num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr, num_ptr);
			break;
		case 3:
			init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr); break;
		default: printf("请重新输入");
			candidates_menu(num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr, num_ptr);
			break;
		}
	}

	
}