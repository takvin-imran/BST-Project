#include <iostream>
#include <fstream>
using namespace std;

struct node
{
    int sku;
    string productName;
    float productPrice;
    node *left;
    node *right;
};

node *createNode(int sku, string pName, float price){
    node *temp= new node();
    temp->sku=sku;
    temp->productName=pName;
    temp->productPrice=price;

    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

node *addProduct(node *head, int sku, string pName, float price){
    if(head == NULL){
        head=createNode(sku, pName, price);
        return head;
    }
    else if(sku <= head->sku){
        head->left=addProduct(head->left, sku, pName, price);
    }
    else {
        head->right=addProduct(head->right, sku, pName, price);
    }
    return head;
}

node *findProduct(node *head, int sku){
    node *temp=NULL;
    if(head==NULL){
        return temp;
    }
    else if(head->sku==sku){
        return head;
    }
    else if(sku<=head->sku){
        return findProduct(head->left, sku);
    }
    else{
        return findProduct(head->right, sku);
    }
}
node *minValueNode(node *head){
    node *current = head;
    while(current && current->left!=NULL){
        current=current->left;
    }
    return current;
}

node *deleteProduct(node *head, int sku){
    node *temp=NULL;
    if(head==NULL){
        return head;
    }
    else if(sku<head->sku){
        head->left=deleteProduct(head->left, sku);
    }
    else if(sku>head->sku){
        head->right=deleteProduct(head->right, sku);
    }
    else{
        if(head->left==NULL && head->right==NULL){
            return NULL;
        }
        else if(head->left==NULL){
            temp=head->right;
            free(head);
            return temp;
        }
        else if(head->right == NULL){
            temp = head->left;
            free(head);
            return temp;
        }
        temp= minValueNode(head->right);
        head->sku=temp->sku;
        head->productName=temp->productName;
        head->productPrice = temp->productPrice;

        head->right = deleteProduct(head->right, temp->sku);
    }
    return head;
}

int minCoins(int coins[], int totalCoin, int value)
{
    if (value == 0)
        return 0;

    int res = INT_MAX;

    for (int i = 0; i < totalCoin; i++)
    {
        if (coins[i] <= value)
        {
            int sub_res = 1 + minCoins(coins, totalCoin, value - coins[i]);
            if (sub_res < res)
                res = sub_res;
        }
    }
    return res;
}



void showProductList(node *head){
    if(head==NULL){
        return;
    }
    showProductList(head->left);
    cout << "SKU: " << head->sku << endl;
    cout << "Product Name: " << head->productName << endl;
    cout << "Price: " << head->productPrice << endl <<endl;
    showProductList(head->right);
}
float totalCartValue(node *head){
    if(head==NULL){
        return 0;
    }
    return (head->productPrice + totalCartValue(head->left)+ totalCartValue(head->right));
}


node *readProductInfo(node *head){
    ifstream read;
    int sku;
    string pName;
    float price;

    read.open("ProductList.txt");
    if(!read.fail()){
        while(!read.eof()){
            read>>sku;
            read>>pName;
            read>>price;
            head=addProduct(head, sku, pName, price);
        }
    }
    read.close();
    return head;
}



int main(){
    node *head=NULL;
    node *cart=NULL;
    node *temp;
    int sku;
    string productName;
    float productPrice;
    int key;

    int coins[] = {20, 10, 5, 2, 1 };
    int total_coins = 5;

    head = readProductInfo(head);

    while(true){
        cout   << endl << "1. Add Product"
               << endl << "2. Show Product List"
               << endl << "3. Search Product"
               << endl << "4. Add Product in the cart"
               << endl << "5. Product In the Cart"
               << endl << "6. Delete Product From Cart"
               << endl << "7. Checkout";
        cout << endl << "Select Option: ";
        cin >> key;

        switch(key){
        case 1:
            cout << endl << "Enter SKU number :";
            cin >> sku;
            cout << "Enter Product Name :";
            cin >> productName;
            cout << "Enter Product Price :" ;
            cin >> productPrice;

            head = addProduct(head, sku, productName, productPrice);
            break;
        case 2:
            cout << "------------Product List------------" << endl;
            showProductList(head);
            break;
        case 3:
            cout << endl << "Find Product :";
            cin >> sku;
            temp=findProduct(head, sku);
            if(temp!=NULL){
                cout << "SKU: " << temp->sku << endl;
                cout << "Product Name: " << temp->productName << endl;
                cout << "Price: " << temp->productPrice << endl <<endl;
            }
            else{
                cout << "There is no product with this SKU :" << sku << endl;
            }
            break;
        case 4:
            cout << "Enter SKU to add product in the Cart"<< endl;
            cout << endl << "SKU : ";
            cin >> sku;
            temp=findProduct(head, sku);
            if(temp!=NULL){
                cart = addProduct(cart, temp->sku, temp->productName, temp->productPrice);
                cout << "Product Added In The Cart" << endl;
            }
            else{
                cout << "There is no product with this SKU :" << sku << endl;
            }
            break;
        case 5:
            cout << "------------Cart Products------------" << endl;
            showProductList(cart);
            cout << "Total Cart Price:" << totalCartValue(cart);
            break;
        case 6:
            cout << endl << "SKU : ";
            cin >> sku;
            temp=deleteProduct(cart, sku);
            showProductList(cart);
            break;
        case 7:
            cout << "------------Cart Products------------" << endl;
            showProductList(cart);
            float totalPrice = totalCartValue(cart);
            float taken;
            cout << "Total Cart Price:" << totalPrice;
            cout << endl << "Enter taken amount form customer: ";
            cin >> taken;
            if(taken>totalPrice){
                totalPrice = taken - totalPrice;
                cout << "Minimum Coins Required: " << minCoins(coins, total_coins, (int)totalPrice) <<endl;
                for (int i = 0; i < total_coins; i++) {
                    if (totalPrice >= coins[i] && totalPrice != 0) {
                    int ans = totalPrice / coins[i];
                    cout << "Coin Value " << coins[i] << ": " << ans <<" Pieces" <<endl;
                    totalPrice = totalPrice - (coins[i] * ans);
                    }
                }
            }
            break;
        }
    }

}
