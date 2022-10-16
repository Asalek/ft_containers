### FT_Container

allocate and deallocate are simply low level memory management and do not play a part in object construction and destruction. This would mean that the default usage of the keywords new and delete would not apply in these functions. As any intermediate C++ programmer should know, the following code
```
A* a = new A;
delete a;
```

is actually 1interpreted by the compiler as :

```
A* a = ::operator new(sizeof(A)); 
a->A::A();
if ( a != 0 ) {  // a check is necessary for delete
    a->~A();
    ::operator delete(a);
}
```

- Allocators
<p>
The purpose of the allocator is to allocate raw memory without construction of objects, as well as simply deallocate memory without the need to destroy them, hence the usage of operator new and operator delete directly is preferred over the usage of the keywords new and delete.
</p>