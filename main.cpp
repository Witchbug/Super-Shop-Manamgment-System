//Project Name: Super Shop Management System



#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

//****************************** Base Class:  Product*****************
class Product
{
    int pid;
    char name[50];
    float price;
public:
    float p_available, p_sold;
    Product()
    {
        p_sold=0.0;
    }
    void create_product ()//Taking input from Admin to store data
    {
        cout<<"\nProduct ID  : ";
        cin>>pid;
        cout<<"\nProduct Name: ";
        cin>>name;
        cout<<"\nUnit Price  : ";
        cin>>price ;
        cout<<"\nQuantity    : ";
        cin>>p_available;

    }


    int call_id()
    {
        return pid;
    }

    float call_price()
    {
        return price;
    }

    float call_p_available()
    {
        return p_available;
    }

    float call_p_sold()
    {
        return p_sold;
    }

    char* call_name()
    {
        return name;
    }

};//End of Product Class


fstream fp;//Global Declaration of Stream Obj
Product p_obj;//Global Declaration of Product Obj


//******************Global Function to show all products*********************
void show_all()
{
    cout<<"\n\n\n\t\t*************List of All Products************\n\n\n\n";
    fp.open("data.dat",ios::in);
    if(!fp)
    {
        cout<<"Sorry File Does Not Exists";
        cout<<"\n\n\n:::Program is Closing.........";
        system("pause");
        exit(0);

    }
    cout<<"ID\t\tProduct NAME\t\tPRICE\t\tSold Qty\tAvailable Qty\n";
    cout<<"***********************************************************************************************\n";
    while(fp.read((char*)&p_obj,sizeof(Product)))
    {
        cout<<p_obj.call_id()<<"\t\t"<<p_obj.call_name()<<"\t\t\t"<<p_obj.call_price()<<"\t\t\t"<<p_obj.call_p_sold()<<"\t\t\t"<<p_obj.call_p_available()<<endl;
    }
    fp.close();

}//End of Show All Function















/*----------------------------Customer Class Start----------------------------------------------*/
class Customer
{
public:

    float check_availability(int id)//function for checking available item
    {
        float available;
        fp.open("data.dat",ios::in);//opening file
        fp.read((char*)&p_obj,sizeof(Product));//reading file
        while(!fp.eof())
        {
            if(p_obj.call_id()==id)//matching the id
            {
                available=p_obj.call_p_available();//storing available item into available variable
                fp.close();
                break;
            }
            fp.read((char*)&p_obj,sizeof(Product));
        }

        return available;
    }



//***************************************** Function for Customer Order ************************
    void customer_order()//function for taking order for customers
    {
        int order_pid[50],counter=0;
        float quantity[50],amount,total=0;
        char ch='Y';
        show_all();
        cout<<"\n\n";
        cout<<"\t\t\n=================================================";
        cout<<"\t\t\n              PLACE YOUR ORDER ";
        cout<<"\t\t\n=================================================";
        do
        {
            cout<<"\t\t\n\nEnter The Product ID : ";
            cin>>order_pid[counter];
            int check_avl=0;
            cout<<"\t\t\nQuantity of the product : ";
            do// do while loop for checking availability and taking right input
            {
                cin>>quantity[counter];
                if(quantity[counter]>check_availability(order_pid[counter]))
                {
                    cout<<"\t\t\n\nYour Quantity exceeds Current availability, Please Enter valid Quantity\n\n";
                    check_avl=1;
                }
                else
                {
                    check_avl=0;
                }
            }
            while(check_avl==1);

            counter++;
            cout<<"\t\t\nDo You Want Another Product ? (y/n)";
            cin>>ch;
        }
        while (ch=='y'||ch=='Y');
        cout<<"\\t\tn\nThank You For your Order";
        system("cls");
        cout<<"\t\t\n\n**************************INVOICE*****************************\n";
        cout<<"\t\t\nSL.\tProduct Name\tQuantity\tUnit Price\tAmount\n";

        for(int x=0; x<=counter; x++)
        {
            fp.open("data.dat",ios::in|ios::out);
            fp.read((char*)&p_obj,sizeof(Product));
            while(!fp.eof())
            {
                if(p_obj.call_id()==order_pid[x])
                {
                    amount=p_obj.call_price()*quantity[x];//price*quantity

                    cout<<"\t\t\n"<<(x+1)<<"\t"<<p_obj.call_name()<<"\t\t\t"<<quantity[x]<<"\t\t"<<p_obj.call_price()<<"\t"<<amount;
                    total+=amount;


                    //updating availability and sold item according to current quantity
                    p_obj.p_available-=quantity[x];
                    p_obj.p_sold+=quantity[x];
                    int pos=-1*sizeof(p_obj);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&p_obj,sizeof(Product));
                    //updating end


                }


                fp.read((char*)&p_obj,sizeof(Product));
            }
            fp.close();
        }

        cout<<"\n\n\t\t**************************************************************\n\n";
        cout<<"\n\t\t\t\t\t\t\t\tTOTAL Bill= "<<total<<endl;
        cout<<"\n\t\t\t\t\t\t\t\tPaid Amount= ";
        float paid;
        cin>>paid;
        float change;
        change=(total-paid);
        cout<<"\n\t\t\t\t\t\t\t\tChange = "<<change<<endl;
        cout<<"\n\t\t\tThanks for shopping with us\n\t\t\tWelcome Again\n\n\n";
    }//End Of Customer Order


//--------------------------------------Customer menu--------------------
    void customer_menu()
    {
        bool entry=true;
        char cus_input;

        while(entry)
        {
            cout<<"\n\n\n\t\t\t*******Customer Panel*******\n\n\n";
            cout<<"Please Enter Your Choice :"<<endl;
            cout<<"\t\t1. Add item to basket\n\t\t2. Exit"<<endl;
            cin>>cus_input;
            switch(cus_input)
            {
            case '1':
            {
                system("cls");
                customer_order();
                cout<<"\n\n";
                system("pause");
                system("cls");
                break;
            }
            case '2':
            {
                entry=false;
                system("cls");
                break;

            }
            default:
            {
                cout<<"\n\nWrong Entry!! Please Try Again With Valid Keyword"<<endl<<endl;

            }
            }//end of switch
        }//end of while



    }// End of Customer Menu
};// End of Customer Class




/*------------------------------- Admin Class Start------------------------------------------*/
class Admin: public Product
{
    string id,pass;
public:
    Admin()
    {
        id="admin";
        pass="1234";
    }


    //*********************************Public Function to save product details in a file as obj**************
    void write_product()
    {
        fp.open("data.dat",ios::out|ios::app);
        p_obj.create_product();
        fp.write((char*)&p_obj,sizeof(Product));//writing into file as object of Product class
        fp.close();
        cout<<"\n\nThe Product has been added to database\n\n";

    }


//************************************* Delete Function to delete any product***********************
    void delete_product()
    {
        int id;
        cout<<"\n\n\******** Delete Product Details*********";
        show_all();
        cout<<"\n\nPlease Enter the Product ID to Delete : ";
        cin>>id;
        fp.open("data.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&p_obj,sizeof(Product)))
        {
            if(p_obj.call_id()!=id)
            {
                fp2.write((char*)&p_obj,sizeof(Product));

            }
        }
        fp2.close();
        fp.close();
        remove("data.dat");
        rename("Temp.dat","data.dat");
        cout<<"\n\n\t..Product DELETED...";

    }// End of Delete function



//************************************* Update Function to update any product details***********************
    void update()
    {
        int found=0,id;
        system("cls");
        show_all();
        cout<<"\n\n\tPlease Enter the Product ID to update : ";
        cin>>id;
        fp.open("data.dat",ios::in|ios::out);
        while(fp.read((char*)&p_obj,sizeof(Product)))
        {
            if(p_obj.call_id()==id)
            {


                p_obj.p_sold=0;
                cout<<"\nPlease Enter The New Details Of the Product "<<endl;
                p_obj.create_product();
                int pos=-1*sizeof(p_obj);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&p_obj,sizeof(Product));
                cout<<"\n\n\tRECORD UPDATED";
                found=1;
                fp.close();
                break;

            }
        }
        if(found==0)
                cout<<"\n\nProduct NOT FOUND On This ID";
    }// End of Update Function





    //-------------------------------Admin Menu---------------------------------
    void admin_menu()
    {
        string in_id,in_pass;
        bool loop=true,entry=true;
        char input_admin;
        while(loop)
        {
            system("cls");
            cout<<"\n\n\n\t\t\t****Admin Panel****\n\n\n";
            cout<<"Please Enter Your Username: ";
            cin>>in_id;
            cout<<"\nPlease Enter Your Password: ";
            cin>>in_pass;
            if((id==in_id) && (pass==in_pass))
            {

                while(entry)
                {
                    system("cls");
                    cout<<"\t\t\t****Admin Panel****\n\n\n";
                    cout<<"Please Enter Your Choice: "<<endl;
                    cout<<"\t\t1. Add New Product\n\t\t2. Show All Product\n\t\t3. Update Product\n\t\t4. Delete Product\n\t\t5. Exit\n\n";
                    cin>>input_admin;

                    switch(input_admin)
                    {
                    case '1':
                    {
                        system("cls");
                        write_product();
                        cout<<"\n\n";
                        system("pause");
                        system("cls");
                        break;
                    }
                    case '2':
                    {
                        system("cls");
                        show_all();
                        cout<<"\n\n";
                        system("pause");
                        system("cls");
                        break;
                    }
                    case '3':
                    {
                        system("cls");
                        update();
                        cout<<"\n\n";
                        system("pause");
                        system("cls");
                        break;

                    }
                    case '4':
                    {
                        system("cls");
                        delete_product();
                        cout<<"\n\n";
                        system("pause");
                        system("cls");
                        break;

                    }
                    case '5':
                    {
                        entry=false;
                        system("cls");
                        break;
                    }
                    default:
                    {
                        system("cls");
                        cout<<"\n\nWrong Entry!! Please Try Again With Valid Keyword"<<endl<<endl;
                        system("pause");

                    }
                    }

                    loop=false;
                }
            }
            else
            {
                system("cls");
                cout<<"\n\n\t\t\tWarning : Wrong Username or Password!!!\n\n";
                system("pause");


            }
        }//if condition end


    }//admin function
};//Admin class end





/*-------------------------Main Function-----------------------------------------------------*/

int main()
{

    Admin a_obj;
    Customer c_obj;
    bool entry=true;
    char input;

    while(entry)
    {
        system("cls");
        cout<<"\n\n\t\t***********Welcome To Our Super Shop**********\n";
        cout<<"\n\n\t\tPlease Enter Your Choice :\n"<<endl;
        cout<<"\t\t1. Customer\n\t\t2. Admin Panel\n\t\t3. Exit"<<endl;
        cin>>input;
        switch(input)
        {
        case '1':
        {
            system("cls");
            c_obj.customer_menu();
            break;
        }
        case '2':
        {
            system("cls");
            a_obj.admin_menu();
            break;
        }
        case '3':
        {
            entry=false;
            system("cls");
            exit(1);

        }
        default:
        {
            cout<<"\n\nWrong Entry!! Please Try Again With Valid Keyword"<<endl<<endl;
            system("pause");


        }
        }//end of switch
    }//end of while

    return 0;

}// End of main function
