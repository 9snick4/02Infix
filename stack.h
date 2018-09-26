#ifndef STACK_H
#define STACK_H

#include <cassert>

namespace custom
{

   /*******************************************************
   * STACK
   * A stack that holds stuff
   *******************************************************/
   template <class T>
   class stack
   {
   public:
      // constructors and destructors
      stack() : data(NULL), mNumElements(0), mNumCapacity(0) {}
      stack(int capacity) throw (const char *);
      stack(const stack <T> & rhs) throw (const char *);
      ~stack() { if (mNumCapacity) delete[] data; }

      // assignment operator
      stack & operator = (const stack & rhs) throw (const char *);

      // get info about the stack
      int size() const { return getNumElements(); }
      int capacity() const { return getNumCapacity(); }
      bool empty() const { return getNumElements() == 0; }
      
      // do things to the stack
      void clear() { mNumElements = 0; }
      void push(const T & t) throw (const char *);
      void pop();
      T & top() throw (const char *);
      const T top() const throw (const char *);

      // getters
      int getNumElements() const { return this->mNumElements; }
      int getNumCapacity() const { return this->mNumCapacity; }

   private:
      T * data;
      int mNumElements;
      int mNumCapacity;

   };


   /*******************************************************
   * STACK : NON-DEFAULT CONSTRUCTOR
   * Preallocate the stack to the numElements
   *******************************************************/
   template<class T>
   stack<T>::stack(int capacity) throw(const char *)
   {
      assert(mNumElements >= 0);

      // no data entered, stack is empty
      if (capacity == 0)
      {
         this->mNumCapacity = 0;
         this->mNumElements = 0;
         this->data = NULL;
         return;
      }
      else
      {
         // nothing has been added do start values at 0
         this->mNumElements = 0;
         this->mNumCapacity = 0;

         // attempt to allocate
         try
         {
            data = new T[capacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Stack.";
         }
         // copy over the stuff
         this->mNumCapacity = capacity;
      }
   }

   /*******************************************************
   * STACK : COPY CONSTRUCTOR
   *******************************************************/
   template<class T>
   stack<T>::stack(const stack<T>& rhs) throw(const char *)
   {
      // be sure there is something to copy over
      assert(rhs.mNumCapacity >= 0);

      // if rhs is empty
      if (rhs.mNumElements == 0)
      {
         mNumCapacity = 0;
         mNumElements = 0;
         data = NULL;
         return;
      }

      // if rhs has something in it
      else
      {
         // attempt to allocate 
         try
         {
            data = new T[rhs.mNumElements];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Stack.";
         }

         // copy over the stuff
         assert(rhs.mNumElements >= 0 && rhs.mNumElements <= rhs.mNumCapacity);
         mNumCapacity = rhs.mNumCapacity;
         mNumElements = rhs.mNumElements;
         for (int i = 0; i < mNumElements; i++)
            data[i] = rhs.data[i];
      }
   }

   /*******************************************************
   * STACK : ASSIGNMENT OPERATOR
   *******************************************************/
   template<class T>
   stack <T> & stack <T> :: operator = (const stack <T> & rhs) throw(const char *)
   {
      // be sure there is something to copy
      assert(rhs.mNumCapacity >= 0);

      // allocate more memory if needed
      if (mNumCapacity < rhs.mNumElements)
      {
         T * temp;
         try
         {
            temp = new T[rhs.mNumElements];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for stack.";
         }
         // copy over data as needed
         if (mNumElements)
         {
            for (int i = 0; i < mNumElements; i++)
               temp[i] = data[i];
         }
         // delete the old buffer as needed
         if (mNumCapacity)
            delete[] data;

         // copy data from new array
         data = temp;
         mNumCapacity = rhs.mNumElements;
      }
      
      // make sure we allocated enough memory
      assert(mNumCapacity >= rhs.mNumElements);

      // assign everything over
      for (int i = 0; i < rhs.mNumElements; i++)
         data[i] = rhs.data[i];
      mNumElements = rhs.mNumElements;

      return *this;
   }

   /*******************************************************
   * STACK : PUSH
   * Insert an item on the end of the stack
   *******************************************************/
   template<class T>
   void stack<T>::push(const T & t) throw(const char *)
   {
      // if capacity is at 0, set it to 1, then add new element
      if (mNumElements == 0)
      {
         mNumCapacity = 1;
         if (data != NULL)
            delete[] data;
         try
         {
            data = new T[mNumCapacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Stack.";
         }
         data[mNumCapacity - 1] = t;
         mNumElements = 1;
      }

      // if capacity is same as elements, double capacity then add new element
      else if (mNumCapacity == mNumElements)
      {
         assert(mNumCapacity != 0);
         mNumCapacity *= 2;
         T * temp;
         try
         {
            temp = new T[mNumCapacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Stack.";
         }
         for (int i = 0; i < mNumElements; i++)
            temp[i] = data[i];
         delete[] data;
         data = temp;
         data[mNumElements++] = t;
      }

      // if capacity is big enough, just add new element
      else
      {
         assert(mNumCapacity > mNumElements);
         data[mNumElements++] = t;
      }
   }

   /*******************************************************
   * STACK : POP
   * Remove an item on the end of the stack
   *******************************************************/
   template<class T>
   void stack<T>::pop()
   {
      if (mNumElements == 0)
         return;
      else
      {
         assert(mNumElements != 0);
         --mNumElements;
      }
   }

   /*******************************************************
   * STACK : TOP  
   * Allows the top element of the stack to be changed
   *******************************************************/
   template<class T>
   T & stack<T>::top() throw(const char *)
   {
      if (mNumElements == 0)
         throw "ERROR: Unable to reference the element from an empty Stack";
      else
      {
         assert(mNumElements != 0);
         return data[mNumElements - 1];
      }
   }

   /*******************************************************
   * STACK : CONST TOP
   * Returns the top element of the stack
   *******************************************************/
   template<class T>
   const T & stack<T>::top() const throw(const char *)
   {
      if (mNumElements == 0)
         throw "ERROR: Unable to reference the element from an empty Stack";
      else
      {
         assert(mNumElements != 0);
         return data[mNumElements - 1];
      }
   }


}; // namespace custom

#endif // VECTOR_H

