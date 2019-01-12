from bst import BST
bst1  = BST()
print("hello bst user")
quitloop=False
while quitloop ==False:
    print()
    print("-----------------------------------------------------")
    
    print(" 1.Add To Binary Search Tree ")
    print(" 2.Remove Data in Binary Search Tree ")
    print(" 3.Search Data in Binary Search Tree ")
    print(" 4.Check If Binary Search Tree is Empty or Not ")
    print(" 5.Display The Binary Search Tree ")
    print(" 6.Exit ")
    
    print("-----------------------------------------------------")
    print()
    choices = int(input("Your Choice : "))
    print()

    if choices==1:
        data_to_add = input("Enter A data to Add :")
        bst1.addBST(data_to_add)
    elif choices==2:
        data_to_remove = input("Enter A data to Remove :")
        bst1.removeBST(data_to_remove)
    elif choices==3:
        data_to_search = input("Enter A data to Search :")
        print()
        if bst1.searchBST(data_to_search)==True:
            print("The Data in Binary Search Tree Exist")
            print()
        else:
            print("The Data in Binary Search Tree Does Not Exist")
            print()
    elif choices==4:
        if bst1.isEmpty()==True:
            print("The Binary Search Tree Is Empty")
            print()

        else:
            print("The Binary Search Tree Is NOT Empty")
            print()
    elif choices==5:
        print(bst1.traverseBST())
    elif choices==6:
        quitloop=True
        print("Thank You")
        print()
    else: 
        print("Invalid Choice")
        print()
