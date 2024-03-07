#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER 20
typedef struct {		//ѡ��
	int user_number;		//ѡ����
	char username[20];
	long long phonenumber;
	int vote_number;	//����Ʊ��
}voter;
voter voters_database[MAX_NUMBER] = { 0 };
typedef struct {		//��ѡ��
	long long telephone_number;
	char candidate_name[20];
	long candidate_number;
	int num_of_votes;	//��õ�Ʊ��
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
	int vote_number = 1;		//��ʼƱ��Ϊ1
	int* vote_ptr = &vote_number;
	int current_people = 0;		//����տ�ʼʱѡ��;�ѡ��������Ϊ0
	int* num_ptr = &current_people;
	int current_candidate_people = 0;
	int* num_candidate_ptr = &current_candidate_people;
	int publish = 0;			//ͶƱ����Ƿ񷢲�������
	int* pub_ptr = &publish;

	while (!flag) {
		init(fla, vote_ptr, num_ptr, num_candidate_ptr,pub_ptr);
	}

	return 0;
}
/*���˵���ѡ����ݣ�*/
void init(int* fla, int* vote_ptr, int* num_ptr, int*num_candidate_ptr, int* pub_ptr) {

	while (!*fla) {
		system("cls");
		printf("��ӭ����ͶƱϵͳ��\n\n");
		printf("��ѡ�������ݣ�\n");
		printf("1������Ա\n2����ѡ��\n3��ѡ��\n4���˳�\n\n");
		printf("������ѡ��ǰ�����֣�");

		char identity[MAX_NUMBER] = { 0 };
		gets_s(identity, sizeof(identity));

		if (identity[1] == 0) {		//����Ƿ����롮1����2����3����4��֮��������Լ��Ƿ������˶������
			switch (identity[0]) {
			case '1': administrator_login_system(vote_ptr, num_ptr, fla, num_candidate_ptr, pub_ptr); break;
			case '2': candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla); break;
			case '3': voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla); break;
			case '4': *fla = 1;
				return;
				break;
			default: printf("���������룡");
				system("pause");
				init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr);
				break;
			}
		}
		else {
			printf("���������룡");
			system("pause");
			init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr);
		}

	}

	

}
/*����Ա��½*/
int administrator_login_system(int* vote_ptr, int* num_ptr, int* fla, int*num_candidate_ptr, int* pub_ptr)
{
	/*�ȴ���һ���ļ��������Ա���˻������˻����룬Ȼ����ʾ�û����û������˻��������롣
��ȡ�ļ�������������Ϣ���бȶ���һ�����½�ɹ�*/

	system("cls");
	FILE* first_stream = NULL;
	/*�ԡ�w��ģʽ���ļ����ļ��������򴴽�һ�����ļ�
	  �������ɹ�����0�����ļ�ָ��ָ����ļ�*/
	errno_t err_first = fopen_s(&first_stream, "C:\\Users\\22499\\Desktop\\Administrator_login_information.txt", "w");
	if (err_first != 0 || first_stream == NULL) {
		perror("Error writing file!");
		return EXIT_FAILURE;
	}
	int error_first = fprintf_s(first_stream, "����Ա");		//�����˻������ɹ�����1

	fclose(first_stream);								//�رո��ļ�

	FILE* second_stream = NULL;
	/*�ԡ�a��ģʽ���ļ�*/
	errno_t err_second = fopen_s(&second_stream, "C:\\Users\\22499\\Desktop\\Administrator_login_information.txt", "a");
	if (err_second != 0 || second_stream == NULL) {
		perror("Error appending file!");
		return EXIT_FAILURE;
	}

	int error_second = fprintf_s(second_stream, "\n123456789");			//׷���˻��������ɹ�����1

	fclose(second_stream);
	/*�����Ϣ�Ƿ�洢�ɹ�*/
	if (error_first && error_second) {
		printf("ϵͳ��ʼ���ɹ���\n");
	}

	FILE* stream = NULL;
	/*���ļ���ȡ�ļ�����*/
	errno_t err = fopen_s(&stream, "C:\\Users\\22499\\Desktop\\administrator_login_information.txt", "r");
	if (err != 0 || stream == NULL) {
		perror("Error opening file!");
		return EXIT_FAILURE;
	}
	char buffer[20] = { 0 };
	fscanf_s(stream, "%s", buffer, (unsigned)_countof(buffer));		//��ȡ�ļ��еĹ���Ա����
	long sum = 0;
	fscanf_s(stream, "%ld", &sum);				//��ȡ�ļ��еĹ���Ա����

	fclose(stream);								//�ر��ļ�

	printf("���������Ա�˺�����\n");
	char administrator[20] = { 0 };
	scanf_s("%s", administrator, (unsigned)_countof(administrator));	//�������Ա����

	/*����������ڵ�����*/
	scanf_s("%*[^\n]");
	scanf_s("%*c");

	printf("���������Ա���루����������ɣ�\n");
	long pas = 0;
	scanf_s("%ld", &pas);				//�������Ա����

	scanf_s("%*[^\n]");
	scanf_s("%*c");

	/*�ȶ��������Ϣ���ļ��е���Ϣ�Ƿ�һ��*/
	if ((strcmp(buffer, administrator) == 0) && pas == sum) {
		admin_menu(vote_ptr, num_ptr, num_candidate_ptr,pub_ptr, fla);
		return 0;
	}
	else {
		printf("��½ʧ�ܣ�\n");
		system("pause");
		init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr);
		return 1;
	}

}
/*�Թ���Ա��ݵ�½�ɹ���Ĳ˵�*/
void admin_menu(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla) {
	int flag = 0;

	
		while (!flag) {
			while (!*fla) {
			system("cls");

			printf("��ӭ����Ա��½ͶƱϵͳ��\n");
			printf("��ѡ����Ҫ���еĲ�����\n");
			printf("1���鿴��ѡ����Ϣ\n2���鿴ѡ����Ϣ\n");
			printf("3���޸�ѡ��ÿ���ͶƱ��\n4���޸�ѡ��ʱ��\n");
			printf("5������ͶƱ���\n6���˳�\n");
			printf("������ѡ��ǰ�����֣�");

			char fuction[MAX_NUMBER] = { 0 };
			gets_s(fuction, sizeof(fuction));
			/*����Ƿ����롮1����2����3����4����5��֮��������Լ��Ƿ������˶������*/
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
				default: printf("���������룡");
					system("pause");
					admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
					break;
				}
			}
			else {
				printf("���������룡");
				system("pause");
				admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
			}
		}
			flag = 1;
	  }
	}
/*�޸�ѡ����е�Ʊ��*/
int modify_votes_number(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla) {
	printf("�����ڳ����޸�ѡ��ÿ���ͶƱ����\n");
	printf("���ڣ�ѡ��ÿ���Ͷ %d Ʊ\n", *vote_ptr);
	printf("����Ҫ�޸�����(y/n)\n");	//ѯ���Ƿ�Ҫ�����޸�
	char buffer[MAX_NUMBER] = { 0 };
	gets_s(buffer, sizeof(buffer));
	int changed_number = 0;

	if (buffer[1] == 0) {
		switch (buffer[0])
		{
		case 'y': 	printf("����������Ҫ�ĳɵ�Ʊ����Ʊ������Ϊ�㣩\n");

			scanf_s("%d", &changed_number);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (changed_number == 0) {
				printf("�޸�ʧ�ܣ�");
				system("pause");
				return *vote_ptr;
			}

			int change = changed_number - *vote_ptr;			//�����޸ĺ����޸�ǰƱ����ֵ

			for (int i = 0; i < *num_ptr; i++) {				//����ѡ��Ʊ��
				voters_database[i].vote_number = voters_database[i].vote_number + change;
			}



			if (changed_number != *vote_ptr) {		//����޸�ǰ���ͶƱ���Ƿ���ͬ
				printf("�޸ĳɹ���");
				system("pause");
				return changed_number;
			}
			else {
				printf("�������Ʊ����ѡ��ԭ����ͶƱ����ȣ�\n");
				system("pause");
				return *vote_ptr;
			}

			break;

		case 'n': admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla); 
			return 1;
			break;
		default: printf("���������룡");
			system("pause");
			modify_votes_number(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
			return 1;
			break;
		}
	}
	else {
		printf("���������룡");
		system("pause");
		modify_votes_number(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
		return 1;
	}
}
/*�޸�ѡ��ʱ��*/
date modify_time(int* vote_ptr, int* num_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla) {
	printf("�����ڳ����޸�ѡ��ʱ�䣡\n");
	printf("���ڣ�ѡ��ʱ��Ϊ %d/%d/%d\n", originally_date.year, originally_date.month, originally_date.day);
	printf("���Ƿ�Ҫ�޸�����(y/n)\n");		//ѯ���Ƿ�Ҫ�����޸�
	char buffer[MAX_NUMBER] = { 0 };
	gets_s(buffer, sizeof(buffer));
	date temp_date = { 0 };

	if (buffer[1] == 0) {
		switch (buffer[0])
		{
		case 'y': 	printf("����������Ҫ�޸�Ϊ�����ڣ�������\" / \"���ꡢ�¡��շֿ���:\n");

			scanf_s("%d/%d/%d", &temp_date.year, &temp_date.month, &temp_date.day);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			break;

		case 'n': admin_menu(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla); break;
		default: printf("���������룡");
			system("pause");
			modify_time(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
			break;
		}
	}
	else {
		printf("���������룡");
		system("pause");
		modify_time(vote_ptr, num_ptr, num_candidate_ptr, pub_ptr, fla);
	}

	/*������벻�����ֻ�δ����ʽ���뽫��������Ϊ�㣬���ڼ���Ƿ�ɹ��޸�*/
	if (temp_date.year == 0 || temp_date.month == 0 || temp_date.day == 0) {
		printf("�޸�ʧ�ܣ�");
		system("pause");
		return originally_date;
	}


	if (originally_date.year == temp_date.year && originally_date.month == temp_date.month && originally_date.day == temp_date.day) {
		printf("�޸ĺ��������ԭ������ͬ��\n");
		system("pause");
		return originally_date;
	}
	else {
		printf("�޸ĳɹ���");
		system("pause");
		return temp_date;
	}
}
/*ѡ��ͶƱ*/
void vote(int* num_ptr, int* num_candidate_ptr, int* count_ptr, int* pub_ptr, int* fla, int* vote_ptr) {

	if (*num_candidate_ptr != 0) {
		/*���ѡ��ͶƱ�����Ƿ��ù�*/
		if (voters_database[*count_ptr].vote_number <= 0) {		//ͶƱ�����ù�
			printf("������ͶƱ�����Ѿ��ù��ˣ�\n");
			system("pause");
			voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
		}
		else {
			present_candidates_information(num_candidate_ptr);

			printf("���ѡ�ٽ��ڣ�%d/%d/%d ���У�\n", originally_date.year, originally_date.month, originally_date.day);
			printf("����������֧�ֵľ�ѡ�ߵı�ţ�");

			int buffer = 0;
			scanf_s("%d", &buffer);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (buffer != 0 && buffer <= *num_candidate_ptr) {		//����Ƿ���ȷ�����˾�ѡ�ߵı��
				(candidates_database[buffer - 1].num_of_votes)++;		//��ͶƱ�ľ�ѡ��Ʊ����һ
				(voters_database[*count_ptr].vote_number)--;				//ѡ��ͶƱ������һ
				*pub_ptr = 0;

				printf("ͶƱ�ɹ���");
				system("pause");
			}
			else {
				printf("���������룡");
				system("pause");
				vote(num_ptr, num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr);
			}
		}
	}
	else {
		printf("û�о�ѡ�ߣ�\n");
		system("pause");
		voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
	}
	
}
/*����ͶƱ���*/
int statistical_results(int* num_candidate_ptr, int* pub_ptr) {

	if (*num_candidate_ptr != 0) {
		candidate tem[MAX_NUMBER] = { 0 };
		for (int k = 0; k < *num_candidate_ptr; k++) {
			tem[k] = candidates_database[k];
		}

		/*�Ӵ�С����*/
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

		/*���ԡ�w��ģʽ�򿪻򴴽�һ���ļ���д���һλ��ѡ�ߵ���Ϣ*/
		FILE* result_stream = NULL;
		errno_t err = fopen_s(&result_stream, "C:\\Users\\22499\\Desktop\\result.txt", "w");
		if (err != 0 || result_stream == NULL) {
			perror("Opening failed!");
			return EXIT_FAILURE;
			system("pause");
		}
		fprintf_s(result_stream, "%d %s %d\n", tem[0].candidate_number, tem[0].candidate_name, tem[0].num_of_votes);

		fclose(result_stream);

		/*�ԡ�a��ģʽ���ļ���׷��ʣ�ྺѡ�ߵ���Ϣ*/
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
			printf("ѡ�ٽ���Ѿ��ɹ�������\n");
			system("pause");
			return 0;
		}
		else {
			printf("����ʧ�ܣ�");
			system("pause");
			return 1;
		}
	}
	else {
		printf("û�����ݿɹ�������\n");
		system("pause");
		return 0;
	}

}
/*ѡ��or��ѡ�߲鿴ͶƱ���*/
int see_result(int* pub_ptr, int* num_candidate_ptr) {
	if (*pub_ptr) {
		/*�ԡ�a��ģʽ���ļ�����ʽ����ȡ��Ϣ*/
		FILE* read_stream = NULL;
		errno_t err = fopen_s(&read_stream, "C:\\Users\\22499\\Desktop\\result.txt", "r");
		if (err != 0 || read_stream == NULL) {
			perror("Failed read!");
			return EXIT_FAILURE;
		}
		candidate temp = { 0 };

		printf("ͶƱ������£�\n");
		printf("��� ��ѡ������ ���Ʊ��\n");
		for (int i = 0; i < *num_candidate_ptr; i++) {
			fscanf_s(read_stream, "%d %s %d", &temp.candidate_number, &temp.candidate_name, MAX_NUMBER, &temp.num_of_votes);
			printf("%4d %s %10d\n", temp.candidate_number, temp.candidate_name, temp.num_of_votes);
		}

		fclose(read_stream);

		int all_vote = 0;
		for (int i = 0; i < *num_candidate_ptr; i++) {
			all_vote += candidates_database[i].num_of_votes;
		}

		printf("��ѡ�߻��Ʊ��ռ�����£�\n");
		printf("��ѡ������  ��ѡ��Ʊ��ռ��\n");
		for (int i = 0; i < *num_candidate_ptr; i++) {
			printf("%s %15.f%%\n", candidates_database[i].candidate_name, ((candidates_database[i].num_of_votes + 0.0) / all_vote) * 100);
		}

		system("pause");
		return 0;
	}
	else {
		printf("ͶƱ�����δ�����򷢲���Ϣ��δ���£�");
		system("pause");
		return 1;
	}
}

/*��ʾѡ����Ϣ*/
void present_voters_information(int* vote_ptr, int* num_ptr)
{

	if ((*num_ptr) == 0)     //����Ƿ���ѡ�������ע�� 
	{
		printf("û��ѡ����Ϣ");

		system("pause");

	}
	else
	{
		system("cls");
		printf("ѡ����Ϣ����:\n");
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
/*��ʾ��ѡ�ߵ���Ϣ*/
void present_candidates_information(int* num_candidate_ptr)
{

	if (*num_candidate_ptr == 0)     //����Ƿ��о�ѡ�߽�����ע�� 
	{
		printf("û�о�ѡ����Ϣ");

		system("pause");

	}
	else
	{
		system("cls");
		printf("��ѡ����Ϣ����:\n");
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
/*ѡ��ע��*/
void voters_login_system(int* num_ptr, int* vote_ptr, int* num_candidate_ptr, int* pub_ptr, int* fla)
{
	system("cls");

	printf("�������Ƿ��Ѿ�ע����ѡ���˻���(y/n)\n");     //�ж�ѡ��֮ǰ�Ƿ�ע����˻� y����yes n����no
	char ch;
	scanf_s("%c", &ch, 1);

	switch (ch)
	{
	case 'y':
	{
		printf("�����������û�����\n");
		char temp_name[MAX_NUMBER] = { 0 };
		scanf_s("%s", temp_name, MAX_NUMBER);

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		int flag = 0;
		int count = 0;
		for (int i = 0; i < *num_ptr && !flag; i++)
		{
			if (!strcmp(temp_name, voters_database[i].username))     //�ж��û����Ƿ���� 
			{
				flag = 1;
				count = i;
			}
		}

		if (flag) {          //�û������� ���������ֻ���
			printf("�����������ֻ����룺\n");
			long long temp_num = 0;
			scanf_s("%zd", &temp_num);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (temp_num == voters_database[count].phonenumber)     //��Ϣƥ�� ��¼�ɹ�      
			{
				printf("��½�ɹ���");
				system("pause");

				int* count_ptr = &count;

				voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);      //����ѡ��˵�
			}
			else                              //��Ϣ��ƥ�� ��¼ʧ�� 
			{
				printf("��Ϣ��ƥ�䣬��½ʧ�ܣ�");
				system("pause");
				voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);     //����ѡ��ע��ϵͳ
			}
		}
		else {                    //�û���������
			printf("���û������ڣ�\n");
			system("pause");
			voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
		}

	} break;
	case 'n':
	{                                         //�ж�ѡ�������Ƿ�����
		if (*num_ptr == MAX_NUMBER)          //ѡ����������
		{
			printf("��������");
			system("pause");
			voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
		}
		printf("--------------------\n");
		printf("��ӭ����ѡ��ע��ϵͳ\n");     //ѡ������δ�� ����ѡ��ע��ϵͳ
		printf("--------------------\n");
		int a = 0;
		long long new_telephone_number = 0;
		printf("�������ֻ�����ע���Ϊѡ��");
		scanf_s("%zd", &new_telephone_number);
		for (a = 0; a < *num_ptr; ++a)     //�ж���������ֻ����Ƿ�ע���
			if (voters_database[a].phonenumber == new_telephone_number)     //�ֻ�����ע��   
			{
				printf("���ֻ�����ע��");
				system("pause");
				voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
			}
		voters_database[a].phonenumber = new_telephone_number;//�ֻ���δע�� ������ֻ���
		printf("�������ֻ���ӵ���ߵ�������");
		scanf_s("%s", voters_database[a].username, MAX_NUMBER);
		++(*num_ptr);
		voters_database[a].user_number = *num_ptr;
		voters_database[a].vote_number = *vote_ptr;
		printf("ѡ��ע��ɹ�\n");

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		system("pause");
		init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr); break;
	}
	default:
		printf("���������룡");
		voters_login_system(num_ptr, vote_ptr, num_candidate_ptr, pub_ptr, fla);
		break;
	}
}
/*��ѡ��ע��*/
void candidates_login_system(int* num_candidate_ptr, int* pub_ptr, int* vote_ptr, int* num_ptr, int* fla)
{
	system("cls");

	printf("�������Ƿ��Ѿ�ע���˾�ѡ���˻���(y/n)\n");     //�ж�ʹ�����Ƿ��Ѿ�ע����˺� y����yes n����no
	char ch;
	scanf_s("%c", &ch, 1);

	switch (ch)
	{
	case 'y':
	{
		printf("�����������û�����\n");
		char temp_name[MAX_NUMBER] = { 0 };
		scanf_s("%s", temp_name, MAX_NUMBER);

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		int flag = 0;
		int count = 0;
		for (int i = 0; i < *num_candidate_ptr && !flag; i++)
		{
			if (!strcmp(temp_name, candidates_database[i].candidate_name))     //�ж��û����Ƿ���� 
			{
				flag = 1;
				count = i;
			}
		}

		if (flag)                    //�û������� ���������ֻ��� 
		{
			printf("�����������ֻ����룺\n");
			long long temp_num = 0;
			scanf_s("%zd", &temp_num);

			scanf_s("%*[^\n]");
			scanf_s("%*c");

			if (temp_num == candidates_database[count].telephone_number)     //��Ϣƥ�� ��¼�ɹ� 
			{
				printf("��½�ɹ���");
				system("pause");

				int* count_ptr = &count;

				candidates_menu(num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr, num_ptr);     //�����ѡ�߲˵�

			}
			else                              //��Ϣ��ƥ�� ��¼ʧ�� 
			{
				printf("��Ϣ��ƥ�䣬��¼ʧ��");
				system("pause");
				candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);     //�����ѡ��ע��ϵͳ
			}
		}
		else                    //�û��������� 
		{
			printf("���û������ڣ�\n");
			system("pause");
			candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);
		}

	} break;
	case 'n':
	{                    //�жϲ�ѡ�������Ƿ�����
		if (*num_candidate_ptr == MAX_NUMBER)          //��ѡ����������
		{
			printf("��������");
			return;
		}
		printf("------------------------\n");
		printf("��ӭ���뾺ѡ��ע��ϵͳ\n");          //��ѡ������δ�� �����ѡ����ע��ϵͳ
		printf("------------------------\n");
		int a = 0;
		long long new_telephone_number = 0;
		printf("�������ֻ�����ע���Ϊ��ѡ�ߣ�");
		scanf_s("%zd", &new_telephone_number);

		for (a = 0; a < *num_candidate_ptr; ++a)     //�ж���������ֻ����Ƿ�ע���
			if (candidates_database[a].telephone_number == new_telephone_number)     //�ֻ�����ע��
			{
				printf("���ֻ�����ע��");
				system("pause");
				candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);
			}
		candidates_database[a].telephone_number = new_telephone_number;//�ֻ���δע�� ������ֻ���
		printf("�������ֻ���ӵ���ߵ�������");
		scanf_s("%s", candidates_database[a].candidate_name, MAX_NUMBER);
		++(*num_candidate_ptr);
		candidates_database[a].candidate_number = *num_candidate_ptr;
		candidates_database[a].num_of_votes = 0;
		printf("��ѡ��ע��ɹ�\n");
		*pub_ptr = 0;

		scanf_s("%*[^\n]");
		scanf_s("%*c");

		system("pause");
		init(fla, vote_ptr, num_ptr, num_candidate_ptr, pub_ptr); break;
	}
	default:
		printf("���������룡");
		system("pause");
		candidates_login_system(num_candidate_ptr, pub_ptr, vote_ptr, num_ptr, fla);
		break;
	}
}
/*ѡ��˵�*/
void voters_menu(int* num_candidate_ptr, int* count_ptr, int* num_ptr, int* pub_ptr, int* fla, int* vote_ptr)
{
	while (!*fla) {
		system("cls");

		printf("��ӭ%s����ͶƱϵͳ��\n", voters_database[*count_ptr].username);
		printf("��ѡ������Ҫ���еĲ���������ѡ��ǰ����ż��ɣ�:\n");
		printf("1:�鿴��ѡ����Ϣ\n2:ͶƱ\n3:�鿴ͶƱ���\n4:�˳�\n");

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
		default: printf("���������룡");
			voters_menu(num_candidate_ptr, count_ptr, num_ptr, pub_ptr, fla, vote_ptr);
			break;
		}
	}

	
}
/*��ѡ�߲˵�*/
void  candidates_menu(int* num_candidate_ptr, int* count_ptr, int* pub_ptr, int* fla, int*vote_ptr, int* num_ptr)
{
	while (!*fla) {

		system("cls");

		printf("��ӭ���뾺ѡ�߲˵���\n");
		printf("��ѡ������Ҫ���еĲ���(����ѡ��ǰ����ż��ɣ���\n");
		printf("1:�鿴��ѡ����Ϣ\n2:�鿴��ǰͶƱ��Ϣ����\n3:�˳�\n");

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
		default: printf("����������");
			candidates_menu(num_candidate_ptr, count_ptr, pub_ptr, fla, vote_ptr, num_ptr);
			break;
		}
	}

	
}