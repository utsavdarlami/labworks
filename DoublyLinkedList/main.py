from DoublyLInkedList import LinkedList
l = LinkedList()
l.add("Head")
print()
l.traverse()
l.add("it should be head now")
print("-------2 added----")
y=l.retrieve("Head")
l.add(0)
l.add(11,y)
l.traverse()

print("reverse")
l.reverse()

x=l.retrieve("Head")
print("the pointer of head is :")
print(x)

print("-------4 added----")
l.add(4,x)
l.traverse()

y=l.retrieve(4)
print("the pointer of 4 is :")
print(y)

print()
print("-------77 added----")
l.add(77,y)
l.traverse()
l.add(44)
print()

print('.....')

l.traverse()

print()

print('.....')


print("reverse")
l.reverse()