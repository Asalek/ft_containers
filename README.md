# FT_Container

allocate and deallocate are simply low level memory management and do not play a part in object construction and destruction. This would mean that the default usage of the keywords new and delete would not apply in these functions. As any intermediate C++ programmer should know, the following code :
```
A* a = new A;
delete a;
```

is actually interpreted by the compiler as :

```
A* a = ::operator new(sizeof(A)); 
a->A::A();
if ( a != 0 ) {  // a check is necessary for delete
    a->~A();
    ::operator delete(a);
}
```

### Iterators
```
{
///  Marking input iterators.
  struct input_iterator_tag {};
  ///  Marking output iterators.
  struct output_iterator_tag {};
  /// Forward iterators support a superset of input iterator operations.
  struct forward_iterator_tag : public input_iterator_tag {};
  /// Bidirectional iterators support a superset of forward iterator
  /// operations.
  struct bidirectional_iterator_tag : public forward_iterator_tag {};
  /// Random-access iterators support a superset of bidirectional iterator
  /// operations.
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}
```

### Allocators
<p>
The purpose of the allocator is to allocate raw memory without construction of objects, as well as simply deallocate memory without the need to destroy them, hence the usage of operator new and operator delete directly is preferred over the usage of the keywords new and delete.
</p>

### SFINAE

SFINAE stands for "substitution failure is not an error."

### Explicit

Explicit Keyword in C++ is used to mark constructors to not implicitly convert types in C++. It is optional for constructors that take exactly one argument and work on constructors(with a single argument) since those are the only constructors that can be used in typecasting.

### RED_BLACK_TREE

1. A node is either red or black
2. The root and leaves (NIL) are black
3. if a node is red, then its children are black
4. All paths from a node to its NIL descendants contain the same number of black nodes


- RED_BLACK_TREE time complexity is O(log n)

## sources :

SFINAE :
		https://www.youtube.com/watch?v=mNxAqLVIaW0&ab_channel=WolfSound

enable_if :
		https://www.youtube.com/watch?v=H-m23Vvzcug&t=482s

C++ tutorial :
		https://github.com/Asalek/Cpp_Module

Iterator Taraits: it's made for te pointer that not iterators but behave like itertors :
		https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
Explicit :
		https://www.youtube.com/watch?v=j4iZ50lp9KM

Map Iterator :
		https://stackoverflow.com/questions/12259571/how-does-the-stdmap-iterator-work
Rebind		:
		https://stackoverflow.com/questions/14148756/what-does-template-rebind-do
RED_BLACK_TREE:
	Insertion_Deletions_Fixes :
		https://www.youtube.com/watch?v=qvZGUFHWChY&list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin&ab_channel=MichaelSambol
	red black tree algorithme :
		https://www.programiz.com/dsa/red-black-tree
	insertion:
		https://www.programiz.com/dsa/insertion-in-a-red-black-tree
	delete :
		https://www.youtube.com/watch?v=lU99loSvD8s&ab_channel=MichaelSambol
	fix after delete :
		https://www.youtube.com/watch?v=iw8N1_keEWA&ab_channel=MichaelSambol
	
