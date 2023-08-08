#include <iostream>
#include <math.h>
using namespace std;

void setInformation(double& r,double& f,int& n,int& m,double& i,double& am,double& t){

	    cout<<"Enter the coupon rate r:"<<endl;
	    cin>>r;

	    cout<<"Enter the face value F:"<<endl;
	    cin>>f;

	    cout<<"Enter total coupons n:"<<endl;
	    cin>>n;

	    cout<<"Enter total coupons m per year:"<<endl;
	    cin>>m;

	    int choice=0;
	    cout<<"Choose to enter 1.annual nominal interest rate   2.annual effective interest rate"<<endl;
	    cin>>choice;
	    if(choice==1){
	    	cout<<"Enter the annual nominal interest rate:"<<endl;
	    	cin>>am;
	    	i=pow((1+am/m),m)-1;
	    }
	    else{
	    	cout<<"Enter the annual effective interest rate:"<<endl;
	    	cin>>i;
	    	am=m*(pow(1+i,(double)1/m)-1);
	    }

	    t=(double)1/m;


	   cout<<"The information has been successfully input"<<endl;


}

double convert(int&c){
   if(c==0){

	cout<<"Choose:"<<endl;
	cout<<"1.Convert annual nominal interest rate to coupon rate over a coupon date"<<endl;
	cout<<"2.Convert annual nominal interest rate to annual effective interest rate"<<endl;
	cout<<"3.Exit."<<endl;
	cout<<"Please choose:"<<endl;
	cin>>c;
	cout<<endl;

   }


	if(c==1){
        cout<<"Enter annual nominal interest rate:"<<endl;
        double a1;
        cin>>a1;
        cout<<endl;
        cout<<"Enter times m in a year:"<<endl;
        double m;
        cin>>m;
        cout<<endl;
        return a1/m;
	}

	else if(c==2){
		cout<<"Enter annual nominal interest rate:"<<endl;
		double a1;
		cin>>a1;
		cout<<endl;
		cout<<"Enter times m in a year:"<<endl;
		double m;
		cin>>m;
		cout<<endl;
        double i=0.0000;
        i=pow((1+a1/m),m)-1;
        return i;
	}

	else
		return 0.00;

}

double PV1(const int&n,const double&r,const double&f,const double&am, const int&m){

	  double pv=0.0000;

      double j=0.0000;
      j=am/m;

      pv=f*r*(1-pow(1+j,-n))/j+f/pow(1+j,n);
      return pv;

}

double PV2(const int&n,const double&r,const double&f,const double&am, const int&m){
	int choice1=0;
	int choice2=0;
	double s0=0.0000;
	double pv=0.0000;
	cout<<"Choose the type of term structure:"<<endl;
	cout<<"1.The term structure is flat:"<<endl;
	cout<<"2.The term structure is not flat:"<<endl;
	cin>>choice1;
	if(choice1==1){
		cout<<"Enter the term structure s0:"<<endl;
		cin>>s0;
		cout<<"Choose the type of coupon payments:"<<endl;
	    cout<<"1. same  2.different"<<endl;
	    cin>>choice2;
	   if(choice2==1){
		   pv=PV1(n,r,f,am,m);
		   return pv;
	     }
	   if(choice2==2){
            cout<<"Do that by calculator"<<endl;
            return 0.00000;

	   }
	}


	if(choice1==2){

		cout<<"Enter the total number of spot rates: "<<endl;
		int num=0;
		cin>>num;
		double ts[num][2];
		for(int i=0;i<num;i++){
			cout<<"Enter the spot rate with the corresponding coupon period (unit is coupon period)"<<endl;
			cin>>ts[i][0];
			cout<<endl;
			cin>>ts[i][1];
		}
		double f=0.0000;
		cout<<"Enter the face value:"<<endl;
		cin>>f;
		double r=0.0000;
		cout<<"Enter the coupon rate to compute coupon payment for one period:"<<endl;
		cin>>r;
		double c=f*r;
		double pv=0.0000;
		for(int i=0;i<num;i++){
		pv+=c/pow(1+ts[i][0],ts[i][1]);
		}
		pv+=f/pow(1+ts[num-1][0],ts[num-1][1]);

		return pv;
	}
		return 0.0000;

	}

double PV3(const double& r,const double& f,const int& n,const double& i,const double& t ){
     double coupon=f*r;
     double pv=0.0000000;
     double k=t;
     for(int j=1;j<n+1;j++){
    	pv+=coupon/pow(1+i,k);
    	k+=t;
     }
     k-=t;
     pv+=f/pow(1+i,k);
     return pv;
}

double dmac(const double& r,const double& f,const int& n,const int& m,const double& i,const double& am,const double& t){
     //  cout<<r<<" "<<f<<" "<<n<<" "<<m<<" "<<i<<" "<<am<<" "<<t<<endl;
	   double coupon=f*r;
	   double numerator=0.0000;
	   double denominator=0.0000;
	   double tk=t;
	   for(int j=1;j<n+1;j++){
		  numerator=numerator+tk*coupon/pow(1+i,tk);
		 // cout<<"pow(1+i,tk): "<<pow(1+i,tk);
		  denominator=denominator+coupon/pow(1+i,tk);
		 // cout<<"tk: "<<tk<<endl;
		  //cout<<"denominator: "<<denominator<<endl;
		  tk+=t;
	   }
	   tk-=t;
	   numerator+=f*tk/pow(1+i,tk);
	   denominator+=f/pow(1+i,tk);

	   //cout<<"The denominator is "<<denominator<<endl;

	   if(denominator>0.000001){
	       double dmac1=numerator/denominator;
	       cout<<"The Dmac is "<<dmac1<<endl;
	       return dmac1;
	   }
	   else
	      return 0.0000;
}

double dmod(const double& r,const double& f,const int& n,const int& m,const double& i,const double& am,const double& t){
	double dmac1=dmac(r,f,n,m,i,am,t);
	int choice=0;
	cout<<"Choose the type of interest rate:1.annual effective rate   2.annual nominal rate:"<<endl;
	cin>>choice;
	if(choice==1){
		double dmod1=dmac1/(1+i);
		cout<<"The modified duration is "<<dmod1<<endl;
		return dmod1;
	}
	else{
		double dmod1=dmac1/(1+am/m);
		cout<<"The modified duration is "<<dmod1<<endl;
		return dmod1;
	}
}

double firstE(const double& r,const double& f,const int& n,const int& m,const double& i,const double& am,const double& t){
	double pv=PV1(n,r,f,am,m);
	double e=0.0000;
	cout<<"Enter the change e in interest rate: "<<endl;
	cin>>e;
	double dmod1=dmod(r,f,n,m,i,am,t);
	double pv1=0.000000;
	pv1=pv-e*dmod1*pv;
	cout<<"The new bond price using first-order approximation is "<<pv1<<endl;

    char a='n';
    cout<<"Do need to calculate percentage error?  y/n"<<endl;
    cin>>a;
  if(a=='y'){
	double percent=0.0000;
	double i1=i+e;
	double am1=m*(pow(1+i1,(double)1/m)-1);
	double pv2=0.0000000;
	pv2=PV1(n,r,f,am1,m);
	cout<<"The exact present value of the new price is "<<pv2<<endl;
	percent=abs((pv2-pv1)/pv2);
	cout<<"The percentage error using first-order approximation is "<<percent<<endl;
   }

	return pv1;
}

double cmod(const double& r,const double& f,const int& n,const int& m,const double& i,const double& am,const double& t){

	   double coupon=f*r;
	   double numerator=0.0000;
	   double denominator=0.0000;
	   double tk=t;
	   for(int j=1;j<n+1;j++){
		  numerator+=tk*(tk+1)*coupon/pow(1+i,tk);
		  denominator+=coupon/pow(1+i,tk);
		  tk+=t;
	   }
	   tk-=t;
	   numerator+=f*tk*(tk+1)/pow(1+i,tk);
	   denominator+=f/pow(1+i,tk);
       denominator=pow(1+i,2)*denominator;

	   if(denominator>0.000001){
	       double cmod1=numerator/denominator;
	       cout<<"The Cmod with annual effective rate is "<<cmod1<<endl;
	       return cmod1;
	   }
	   else
	      return 0.0000;
}

double secondE(const double& r,const double& f,const int& n,const int& m,const double& i,const double& am,const double& t){
	    double pv=PV1(n,r,f,am,m);
		double e=0.0000;
		cout<<"Enter the change e in interest rate: "<<endl;
		cin>>e;
		double dmod1=dmod(r,f,n,m,i,am,t);
		double cmod1=cmod(r,f,n,m,i,am,t);
		double pv1=0.000000;
		pv1=pv-e*dmod1*pv+pow(e,2)*cmod1*pv/2;
		cout<<"The new bond price using second-order approximation is "<<pv1<<endl;

		char a='n';
		    cout<<"Do need to calculate percentage error?  y/n"<<endl;
		    cin>>a;
		  if(a=='y'){
			double percent=0.0000;
			double i1=i+e;
			double am1=m*(pow(1+i1,(double)1/m)-1);
			double pv2=0.0000000;
			pv2=PV1(n,r,f,am1,m);
			cout<<"The exact present value of the new price is "<<pv2<<endl;
			percent=abs((pv2-pv1)/pv2);
			cout<<"The percentage error using first-order approximation is "<<percent<<endl;
		   }

		return pv1;

}


double irr(const double& r,const double& f,const int& n,const int& m,const double& i,const double& am,const double& t){//input H;
	int h=0;
	cout<<"Enter the H (sell in H years)"<<endl;
	cin>>h;
	int n1=h*m;
	int n2=n-n1;
	double i1=0.0000;
	cout<<"Enter the annual effective rate for investment fund: "<<endl;
	cin>>i1;
	//double am1=m*(pow(1+i1,(double)1/m)-1);
	double pv=PV3(r,f,n,i,t);
	cout<<"pv is "<<pv<<endl;
	double pv1=PV3(r,f,n1,i1,t)-f/pow(1+i1,h);
	double fv1=pow(1+i1,h)*pv1;
	cout<<"fv1 is "<<fv1<<endl;
	double pv2=PV3(r,f,n2,i1,t);
	cout<<"pv2 is "<<pv2<<endl;
	double irr=0.0000;
	irr=pow((fv1+pv2)/pv,(double)1/h)-1;
	cout<<"The irr is "<<irr<<endl;
	return irr;

}

int main(){
	int n=0;
	double f=0.0000;
	double r=0.0000;
	double am=0.0000;
	double i=0.0000;
	int m=0;
	double t=0.0000;
	char a='y';

	double pv=0.0000;
	double dmac1=0.0000000;
	double dmod1=0.000000;
	double cov=0.000000;
	double firste=0.000000;
	double seconde=0.00000;
	double irr1=0.000000;

 while(a=='y'){
	int choice=0;
	cout<<"Please select your choice"<<endl;
	cout<<"0.Reset the information"<<endl;
	cout<<"1.Convert the interest rate"<<endl;
	cout<<"2.Compute the PV using method 1"<<endl;
	cout<<"3.Compute the PV using method 2"<<endl;
	cout<<"4.Compute the Macaulay duration Dmac"<<endl;
	cout<<"5.Compute the Modified duration"<<endl;
	cout<<"6.Compute the Modified convexity"<<endl;
	cout<<"7.Compute the new price using first-order approximation"<<endl;
	cout<<"8.Compute the new price using second-order approximation"<<endl;
	cout<<"9.Compute the irr for the whole investment"<<endl;
    cout<<"10.Compute the PV using annual effective interest rate"<<endl;

	cin>>choice;
	if(choice==0){
		setInformation(r,f,n,m,i,am,t);
		cout<<"The information has been successfully reset"<<endl;
	}
	if(choice==1){
		double interest=0.0000;
		int c=0;
		interest=convert(c);
		cout<<"The target interest rate is "<<interest<<endl;
	}
	if(choice==2){
        pv=PV1(n,r,f,am,m);
		cout<<"The present value is "<<pv<<endl;
	}
    if(choice==3){
    	pv=PV2(n,r,f,am,m);
		cout<<"The present value is "<<pv<<endl;
    }

    if(choice==4){
    	dmac1=dmac(r,f,n,m,i,am,t);
    }

    if(choice==5){
    	dmod1=dmod(r,f,n,m,i,am,t);
    }

    if(choice==6){
       cov=cmod(r,f,n,m,i,am,t);
    }

    if(choice==7){
    	firste=firstE(r,f,n,m,i,am,t);
    }

    if(choice==8){
    	seconde=secondE(r,f,n,m,i,am,t);
    }

    if(choice==9){
    	irr1=irr(r,f,n,m,i,am,t);
    }

    if(choice==10){
    	pv=PV3(r,f,n,i,t);
    	cout<<"The present value is "<<pv<<endl;
    }

    cout<<endl;

    cout<<"Continue or not:y or n"<<endl;
    cin>>a;
    while(a!='y'&&a!='n'){
    	cout<<"The input is not valid. Enter again."<<endl;
    	cin>>a;
    }

  }

	return 0;
}



