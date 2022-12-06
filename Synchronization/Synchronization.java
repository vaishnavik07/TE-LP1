import java.util.Scanner;
import java.util.concurrent.Semaphore;

class Counter2{
	static int count=0;
	static int buffer[]=new int[100]; 
}

class DummyThread2 extends Thread{
	String threadName;
	Semaphore semaphore;
	int n;
	public DummyThread2(Semaphore semaphore,String threadName,int n) {
		super(threadName);
		this.threadName=threadName;
		this.semaphore= semaphore;
		this.n=n;
	}
    
	@Override
	public void run()
	{
		if(this.getName().contains(	"Producer")) {
			try {
				semaphore.acquire();
				System.out.println(this.getName()+" acquires lock....");
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			for(int i=0;i<5;i++)
			{
				if(Counter2.count>=n)
				{
					System.out.println("Buffer is full...");
				}
				else if(Counter2.count>=0)
				{
					Counter2.buffer[Counter2.count]=1;
					System.out.println("Set buffer element "+Counter2.count+"=1");
					Counter2.count=Counter2.count+1;
				}
				else {
					//halt(i+1)
				}
				System.out.println(this.getName()+" performs operation: "+(i+1)+"-> Count: "+Counter2.count);
				System.out.println();
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			System.out.println(this.getName()+"	releases lock....");
			semaphore.release();
		}
		else{
			try {
				semaphore.acquire();
				System.out.println(this.getName()+" acquires lock....");
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			for(int i=0;i<5;i++)
			{
				if(Counter2.count<=0)
				{
					System.out.println("Buffer is empty...");
				}
				else if(Counter2.count<=n)
				{
					Counter2.count=Counter2.count-1;
					Counter2.buffer[Counter2.count]=0;
					System.out.println("Set buffer element "+Counter2.count+"= 0");
					
				}
				else {
					//halt
				}
				
				System.out.println(this.getName()+" performs operation: "+(i+1)+"-> Count: "+Counter2.count);
				System.out.println();
				try {
					Thread.sleep(2000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			System.out.println(this.getName()+"	releases lock....");
			semaphore.release();
		}
	}
	
}

public class Semaphore1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
//        System.out.println("Hello World");
		Scanner sc= new Scanner(System.in);
		System.out.println("Enter buffer size: ");
		int n= sc.nextInt();
		System.out.println("Buffer size: "+	n);
		Semaphore semaphore = new Semaphore(2);
		DummyThread2 t1= new DummyThread2(semaphore,"Producer1",n);
		DummyThread2 t2= new DummyThread2(semaphore,"Consumer1",n);
		DummyThread2 t3= new DummyThread2(semaphore,"Producer2",n);
		DummyThread2 t4= new DummyThread2(semaphore,"Consumer2",n);
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		sc.close();
	}

}