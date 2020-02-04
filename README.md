# Calculator

### 최재웅, 안제하

###### 2018.11


___
#### 역할

> <b> 최재웅 </b>
> > 전반적인 개발 및 알고리즘 구성 <br/>

> <b> 안제하 </b> 
> > 알고리즘 구성 및 개발 보조 <br/>

<br>

___
#### 구현한 연산자
> <b> ( + ) 연산자 </b>
> > 덧셈을 진행하는 연산자이다. <br/>
> > 1 + 2 를 입력받을 경우 결과로 3을 출력한다.

> <b> ( - ) 연산자 </b>
> > 뺼셈을 진행하는 연산자이다. <br/>
> > 2 - 1 을 입력받을 경우 결과로 1을 출력한다. <br/>
> > 음수 또한 출력이 가능하다.

> <b> ( * ) 연산자 </b>
> > 곱셈을 진행하는 연산자이다. <br/>
> > 1 * 2 를 입력받을 경우 결과로 2를 출력한다. <br/>
> > ( * ) 연산자의 피연산자로 0을 입력받은 경우 결과는 무조건 0이 출력된다.

> <b> ( / ) 연산자 </b>
> > 나눗셈을 진행하는 연산자이다. <br/>
> > 4 / 2 를 입력받을 경우 결과로 2를 출력한다. <br/>
> > ( / ) 연산자의 피연산자로 0을 입력받은 경우 0의 위치에 따라 결과는 0 혹은 무한대로 출력된다.

> <b> ( % ) 연산자 </b>
> > 나머지 연산을 진행하는 연산자이다. <br/>
> > 4 % 3 을 입력받을 경우 1을 출력한다.

> <b> ( ^ ) 연산자 </b>
> > 거듭 제곱을 진행하는 연산자이다. <br/>
> > 2 ^ 3 을 입력받을 경우 8을 출력한다.

<br>

___
## 알고리즘

#### 입력 방식

> <b> 소스 </b>
```{.c}
char *InPutFunction()
{
	char *Input = malloc(MAXSIZE);
	int i = 0;

	gotoxy(PositionX, PositionY);
	while (Input[i] = _getche())
	{
		i++;
		if (Input[i - 1] == '\n')
		{
			Input[i - 1] = '\0';
			break;
		}
		if (Input[i - 1] == '\b')
		{
			i = i - 2;
		}
	}

	return Input;
}
```

> <b> 소스 설명 </b>
> > getche 함수를 통해 문자를 입력받은 동시에 출력을 한다. <br/> <br/>
> > 만일 입력받은 문자가 '\n' (개행)일 경우, '\n'이 저장되어 있는 배열 인덱스에 '\0' (NULL)을 저장하여, <br/>
> > 문자열의 끝을 표시한 뒤 입력을 종료한다. <br/> <br/>
> > 또는, 입력받은 문자가 '\b' (백 스페이스)일 경우, <br/>
> > '\b' 가 저장되어 있는 배열 인덱스보다 한 칸 더 앞으로 이동하여 재입력을 받는다.

<br/>

___
#### 피연산자 추출

> <b> 소스 </b>
```{.c}
double *NUMBERPOP(char *s)
{
	double *arr = malloc(MAXSIZE);

	char *delimiter = "+-*/%^";
	char *ptoken;
	char *next_token;

	int cnt = 0;

	ptoken = strtok_s(s, delimiter, &next_token);
	while (ptoken != NULL)
	{
		NumCnt++;
		arr[cnt++] = (double)atoi(ptoken);

		ptoken = strtok_s(NULL, delimiter, &next_token);
	}

	return arr;
}
```

> <b> 소스 설명 </b>
> > 프로그래머가 문자를 구별해낼 구별자(delimeter)를 설정하고 <br/>
> > 입력 받은 수식을 구별해서 strtok 함수를  토큰으로 분리한다. <br/> <br/>
> > 토큰들은 분리와 동시에 배열에 저장하여 "피연산자 배열"을 생성한다. <br/> <br/>
> > 여기서 delimeter의 경우 이 프로그램에서 구현되어 있는 6개의 연산자로 지칭한다.

<br/>

___
#### 연산자 추출

> <b> 소스 </b>
```{.c}
char *OPERATORPOP(char *s)
{
	char *ary = malloc(MAXSIZE);

	int i = 0;
	int cnt = 0;

	while (s[i++] != '\0')
	{
		if (s[i - 1] == '+')
		{
			ary[cnt++] = '+';
			OprCnt++;
		}
		if (s[i - 1] == '-')
		{
			ary[cnt++] = '-';
			OprCnt++;
		}
		if (s[i - 1] == '*')
		{
			ary[cnt++] = '*';
			OprCnt++;
		}
		if (s[i - 1] == '/')
		{
			ary[cnt++] = '/';
			OprCnt++;
		}
		if (s[i - 1] == '%')
		{
			ary[cnt++] = '%';
			OprCnt++;
		}
		if (s[i - 1] == '^')
		{
			ary[cnt++] = '^';
			OprCnt++;
		}
	}

	return ary;
}
```

> <b> 소스 설명 </b>
> > 앞서 피연산자 추출에서 strtok 함수를 활용해 입력받은 수식을 분리할 경우 <br/>
> > 기존 입력받은 수식이 저장되어 있던 배열에는 연산자만 남게 된다. <br/> <br/>
> > 연산자 추출은 해당 배열에 존재하는 값이 어떤 연산자인지 구별한다.

<br/>
