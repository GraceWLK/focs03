#include<iostream>
#include<fstream>
#include<stdio.h>
#include<time.h>
#include<cmath>
#include<stdlib.h>
#include<set>
#include<errno.h>

using namespace std;

struct LNode{
        int data;
        LNode *next;
        LNode(const int x, LNode *p=NULL){
            data = x;
            next = p;
        }
        LNode():next(NULL){};
        ~LNode(){}
    };

class List                                 //创建队列类
{
public:
    LNode *front,*rear;
    int len;
    List(){rear = front = NULL;len = 0;}
    ~List();
    bool isEmpty(){return front==NULL;}
    void enList(int x);
    int deList();
};

void List::enList(int x)
{
    if(rear==NULL) front = rear = new LNode(x);
    else{
        rear->next = new LNode(x);
        rear = rear->next;
    }
    len++;
}

int List::deList()
{
    LNode *p = front;
    int value = front->data;
    front = front->next;
    if(front==NULL) rear = NULL;
    delete p;
    len--;
    return value;
}

List::~List()
{
    LNode *p;
    while(front!=NULL){
        p = front;
        front = front->next;
        delete p;
    }
}


class Random {

public:
	long long int mod;
	long long int x;
	Random(){
		mod = 1;
		x = time(0);
		for(int i=0;i<35;i++)
			mod *= 2;
		mod = mod -31;
	}

	double UniformDistribution() {
		return (double) f(x)/mod;
	}

	int destDistribution(int n, double rho){
		double prob = UniformDistribution();
		if(prob > rho)
		{
			return(-1);
		}
		else
		{
			return(f(x)%n);
		}
	}

	long long f(long long a){
		return x = (5*5*5*5*5*a) % mod;
	}
};

struct QNode{
        long long int data;
        QNode *next;
        QNode(const long long int x,QNode *p=NULL){
            data = x;
            next = p;
        }
        QNode():next(NULL){};
        ~QNode(){}
    };

class Queue                                 //创建队列类
{
public:
    QNode *front,*rear;
    int len;
    Queue(){rear = front = NULL;len = 0;}
    ~Queue();
    bool isEmpty(){return front==NULL;}
    void enQueue(long long int x);
    long long int deQueue();
    //long long int getHead(){return front->data;}
    //void remove(long long int d);
};

void Queue::enQueue(long long int x)
{
    if(rear==NULL) front = rear = new QNode(x);
    else{
        rear->next = new QNode(x);
        rear = rear->next;
    }
    len++;
}

long long int Queue::deQueue()
{
    QNode *p = front;
    long long int value = front->data;
    front = front->next;
    if(front==NULL) rear = NULL;
    delete p;
    len--;
    return value;
}

Queue::~Queue()
{
    QNode *p;
    while(front!=NULL){
        p = front;
        front = front->next;
        delete p;
    }
}

double norminv(const double p)
{
    static const double LOW  = 0.02425;
    static const double HIGH = 0.97575;

    /* Coefficients in rational approximations. */
    static const double a[] =
    {
        -3.969683028665376e+01,
            2.209460984245205e+02,
            -2.759285104469687e+02,
            1.383577518672690e+02,
            -3.066479806614716e+01,
            2.506628277459239e+00
    };

    static const double b[] =
    {
        -5.447609879822406e+01,
            1.615858368580409e+02,
            -1.556989798598866e+02,
            6.680131188771972e+01,
            -1.328068155288572e+01
    };

    static const double c[] =
    {
        -7.784894002430293e-03,
            -3.223964580411365e-01,
            -2.400758277161838e+00,
            -2.549732539343734e+00,
            4.374664141464968e+00,
            2.938163982698783e+00
    };

    static const double d[] =
    {
        7.784695709041462e-03,
            3.224671290700398e-01,
            2.445134137142996e+00,
            3.754408661907416e+00
    };

    double q, r;

    errno = 0;

    if (p < 0 || p > 1)
    {
        errno = EDOM;
        return 0.0;
    }
    else if (p == 0)
    {
        errno = ERANGE;
        return -HUGE_VAL /* minus "infinity" */;
    }
    else if (p == 1)
    {
        errno = ERANGE;
        return HUGE_VAL /* "infinity" */;
    }
    else if (p < LOW)
    {
        /* Rational approximation for lower region */
        q = sqrt(-2*log(p));
        return (((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
            ((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
    }
    else if (p > HIGH)
    {
        /* Rational approximation for upper region */
        q  = sqrt(-2*log(1-p));
        return -(((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
            ((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
    }
    else
    {
        /* Rational approximation for central region */
        q = p - 0.5;
        r = q*q;
        return (((((a[0]*r+a[1])*r+a[2])*r+a[3])*r+a[4])*r+a[5])*q /
            (((((b[0]*r+b[1])*r+b[2])*r+b[3])*r+b[4])*r+1);
    }
}

int main()
{
	long long int n, ccslots, m;
	double rho, z;
	ifstream parameter("input.txt", ios::in);
	double paraData;
	int paraIndex = 0;
	while (parameter>>paraData)
    {
        if(paraIndex==0)
            n = paraData;
        else if(paraIndex==1)
            rho = paraData;
        else if(paraIndex==2)
            m = paraData;
        else break;
        paraIndex++;
    };
	z = norminv(pow(0.6, 1/double(n)));
	ccslots = pow((1*z/(1/0.95-1)),2);
	long long int simTime = ccslots*m;
	long int slots = n*n;
	long long int currentTime = 0;
	long int *degrees = new long int[2*n];
	Queue **VOQueue = new Queue*[n];
	long int maxDegree = 0;
	long int maxSlots;
	long long int sum_complexity = 0;
	Random rands;
	ofstream outfile("maxDegree.txt", ios::out);
	ofstream outfile1("Mean_throughput.txt", ios::out);
	ofstream outfile2("slots_vs_.delta.txt", ios::out);
	ofstream outfile3("complexity.txt", ios::out);
	ofstream outfile4("complexity_perSlot.txt", ios::out);
	ofstream outfile5("parameter.txt", ios::out);

	outfile5<<"Switch size: "<<n<<endl;
	outfile5<<"Simulation time: "<<simTime<<endl;
	outfile5<<"Offered load: "<<rho<<endl;

	outfile.close();
	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();
	outfile5.close();

	//degrees, VOQueue initialization
	for(int i=0;i<n;i++)
	{
		degrees[i] = 0;
		degrees[i+n] = 0;
		VOQueue[i] = new Queue[n];
	}

	//simulation begins
	while(currentTime < simTime)
	{
		maxDegree = 0;
		int **requests = new int*[slots];
		for(long int i=0;i<slots;i++)
		{
			requests[i] = new int[n];
			//cout << endl<< "slot="<<i<<": ";
			for(int k=0;k<n;k++)
			{
				int requestDest = rands.destDistribution(n, rho);
				requests[i][k] = requestDest;
				//cout<<requestDest<<", ";
				if(requestDest!=-1)
				{
					//arrivalSlot
					long long int arrivaltime = i + currentTime;
					VOQueue[k][requestDest].enQueue(arrivaltime);
					degrees[k] += 1;
					degrees[requestDest+n] += 1;
				}
			}
		}
		for(int i=0;i<2*n;i++)
		{
			if(maxDegree<degrees[i])
				maxDegree = degrees[i];
		}
		outfile.open("maxDegree.txt", ios::app);
		outfile<<maxDegree<<" ";
		outfile.close();
        //cout<<endl<<maxDegree<<endl;
        int **vertexColor = new int*[2*n];
		for(int i=0;i<n;i++)
		{
		    vertexColor[i] = new int[maxDegree];
		    vertexColor[i+n] = new int[maxDegree];
			for(long int j=0;j<maxDegree;j++)
			{
				vertexColor[i][j] = -1;
                vertexColor[i+n][j] = -1;
			}
		}
		sum_complexity = 0;
		int *minSlot = new int[2*n];
		for(int i=0;i<n;i++)
        {
            minSlot[i] = 0;
            minSlot[i+n] = 0;
            degrees[i] = maxDegree;
            degrees[i+n] = maxDegree;
        }

		for(long int j=0;j<slots;j++)
		{
			for(int i=0;i<n;i++)
			{
				int request = requests[j][i];
				int optemp = 0;
				if(request!=-1)
				{
					bool judge = false;
                    int min1 = minSlot[i];
                    int min2 = minSlot[request+n];
                    int maxMinSlot = min1;
                    if(min1<min2)
                        maxMinSlot = min2;
                    for(int index=maxMinSlot;index<maxDegree;index++)
                    {
                        optemp++;
                        if(vertexColor[i][index]==-1&&vertexColor[request+n][index]==-1)
                        {
                            vertexColor[i][index] = request;
                            vertexColor[request+n][index] = i;
                            if(index==maxMinSlot&&min1==maxMinSlot)
                            {
                                minSlot[i]++;
                            }
                            if(index==maxMinSlot&&min2==maxMinSlot)
                            {
                                minSlot[request+n]++;
                            }
                            judge = true;
                            break;
                        }
                    }
					if(!judge)
					{
						degrees[i]++;
						degrees[request+n]++;
					}
				}
                sum_complexity += optemp;
			}
		}
		maxSlots = 0;
		for(int i=0;i<2*n;i++)
		{
			if(maxSlots<degrees[i])
				maxSlots = degrees[i];
		}
        outfile2.open("slots_vs_.delta.txt", ios::app);
        outfile4.open("complexity_perSlot.txt", ios::app);
		outfile2<<double(maxSlots)/double(maxDegree)<<" ";
		outfile4<<double(sum_complexity)/double(slots)<<" ";
		for(int i=0;i<n;i++)
		{
			degrees[i] = 0;
			degrees[i+n] = 0;
			delete[] vertexColor[i];
			delete[] vertexColor[i+n];
		}
		delete[] vertexColor;
		for(long int i=0;i<slots;i++)
			delete[] requests[i];
		delete[] requests;
		delete[] minSlot;
		currentTime += slots;
		//slots = maxSlots;
        outfile1.open("Mean_throughput.txt", ios::app);
        outfile3.open("complexity.txt", ios::app);
		outfile1<<double(slots)/double(maxSlots)<<" ";
		outfile3<<sum_complexity<<" ";
        outfile1.close();
        outfile2.close();
        outfile3.close();
        outfile4.close();
	}
	//cout<<currentTime<<endl;
	delete[] VOQueue;
	delete[] degrees;
	system("pause");
}
