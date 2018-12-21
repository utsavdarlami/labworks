from  singlylinkedlist import LinkedList
l = LinkedList();

l.removeFromHead();

l.addToTail("1st entered");

print("---------------HHHHHHHHHHH-------------")

l.traverse();

print()

l.removeFromHead();

print("---------------HHHHHHHHHHH-------------")

l.traverse();
print()
l.addToHead("2nd entered");
l.addToTail(5);
l.addToHead("HEAD");
l.addToTail(4)
print()

l.traverse();
print("--------------")

l.addToTail("tail");

l.traverse();

print("-----SEARCH------")
if l.search(4):
    print("Sucess")
else:
    print("No such item")

print()

print("-----SEARCH------")

if l.search("ee"):
    print("Sucess")
else:
    print("No such item")

print()

value = l.retrieve(5)
print(value)
l.add(99,value)
print()

l.traverse();
print()
print()
print("---------------HHHHHHHHHHH-------------")
l.removeFromHead();
l.traverse();

l.addToHead("NewHEad")
l.addToTail("It ends")
l.add(100,l.retrieve(99))
print()
l.traverse();

print()
l.remove(99)
l.traverse();
print()
print()
#l.pre(99);

