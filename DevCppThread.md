Document original : http://www.linuxselfhelp.com/HOWTO/C++Programming-HOWTO-18.html

Others links :

  * Initiation in french :http://franckh.developpez.com/tutoriels/posix/pthreads/
  * POSIX thread (pthread) librarieshttp://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html#SYNCHRONIZATION

# Designing a Thread Class in C++ #

## Introduction ##
Multi threaded programming is becoming ever more popular. This section presents a design for a C++ class that will encapsulate the threading mechanism. Certain aspects of thread programming, like mutexes and semaphores are not discussed here. Also, operating system calls to manipulate threads are shown in a generic form.

## Brief Introduction To Threads ##
To understand threads one must think of several programs running at once. Imagine further that all these programs have access to the same set of global variables and function calls. Each of these programs would represent a thread of execution and is thus called a thread. The important differentiation is that each thread does not have to wait for any other thread to proceed. All the threads proceed simultaneously. To use a metaphor, they are like runners in a race, no runner waits for another runner. They all proceed at their own rate.

Why use threads you might ask. Well threads can often improve the performance of an application and they do not incur significant overhead to implement. They effectively give good bang for a buck. Imagine an image server program that must service requests for images. The program gets a request for an image from another program. It must then retrieve the image from a database and send it to the program that requested it. If the server were implemented in a single threaded approach, only one program could request at a time. When it was busy retrieving an image and sending it to a requestor, it could not service other requests. Of course one could still implement such a system without using threads. It would be a challenge though. Using threads, one can very naturally design a system to handle multiple requests. A simple approach would be to create a thread for each request received. The main thread would create this thread upon receipt of a request. The thread would then be responsible for the conversation with the client program from that point on. After retrieving the image, the thread would terminate itself. This would provide a smooth system that would continue to service requests even though it was busy serviceing other requests at the same time.

## Basic Approach ##
The create a thread, you must specify a function that will become the entry point for the thread. At the operating system level, this is a normal function. We have to do a few tricks to wrap a C++ class around it because the entry function cannot be a normal member function of a class. However, it can be a static member function of a class. This is what we will use as the entry point. There is a gotcha here though. Static member functions do not have access to the this pointer of a C++ object. They can only access static data. Fortunately, there is way to do it. Thread entry point functions take a void **as a parameter so that the caller can typecast any data and pass in to the thread. We will use this to pass this to the static function. The static function will then typecast the void** and use it to call a non static member function.

## The Implementation ##
It should be mentioned that we are going to discuss a thread class with limited functionality. It is possible to do more with threads than this class will allow.

```
class Thread
{
   public:
      Thread();
      int Start(void * arg);
   protected:
      int Run(void * arg);
      static void * EntryPoint(void*);
      virtual void Setup();
      virtual void Execute(void*);
      void * Arg() const {return Arg_;}
      void Arg(void* a){Arg_ = a;}
   private:
      THREADID ThreadId_;
      void * Arg_;

};

Thread::Thread() {}

int Thread::Start(void * arg)
{
   Arg(arg); // store user data
   int code = thread_create(Thread::EntryPoint, this, & ThreadId_);
   return code;
}

int Thread::Run(void * arg)
{
   Setup();
   Execute( arg );
}

/*static */
void * Thread::EntryPoint(void * pthis)
{
   Thread * pt = (Thread*)pthis;
   pthis->Run( Arg() );
}

virtual void Thread::Setup()
{
        // Do any setup here
}

virtual void Thread::Execute(void* arg)
{
        // Your code goes here
}

```

It is important to understand that we are wrapping a C++ object around a thread. Each object will provide an interface to a single thread. The thread and the object are not the same. The object can exist without a thread. In this implementation, the thread does not actually exist until the Start function is called.

Notice that we store the user argument in the class. This is necessary because we need a place to store it temporarily until the thread is started. The operating system thread call allows us to pass an argument but we have used it to pass the this pointer. So we store the real user argument in the class itself and when the execute function is called it can get access to the argument.

**`Thread();`**
This is the constructor.

**`int Start(void * arg);`**
This function provides the means to create the thread and start it going. The argument arg provides a way for user data to be passed into the thread. Start() creates the thread by calling the operating system thread creation function.

**`int Run(void * arg);`**
This is a protected function that should never be tampered with.

**`static void * EntryPoint(void * pthis);`**
This function serves as the entry point to the thread. It simply casts pthis to Thread **and**

**`virtual void Setup();`**
This function is called after the thread has been created but before Execute() is called. If you override this function, remember to call the parent class Execute().

**`virtual void Execute(void *);`**
You must override this function to provide your own functionality.

## Using The Thread Class ##
To use the thread class, you derive a new class. you override the Execute() function where you provide your own functionality. You may override the Setup() function to do any start up duties before Execute is called. If you override Setup(), remember to call the parent class Setup().

## Conclusion ##
This section presented an implementation of a thread class written in C++. Of course it is a simple approach but it provides a sound foundation upon which to build a more robust design.