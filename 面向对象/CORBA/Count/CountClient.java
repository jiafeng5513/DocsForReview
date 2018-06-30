// CountClient.java  Static Client, VisiBroker for Java

class CountClient
{ public static void main(String args[])
  { try
    { // Initialize the ORB
      System.out.println("Initializing the ORB");
      org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init(args, null);

      // Bind to the Count Object
      System.out.println("Binding to Count Object");
      Counter.Count counter = Counter.CountHelper.bind(orb, "My Count");

      // Set sum to initial value of 0
      System.out.println("Setting sum to 0");
      counter.sum((int)0);

      // Calculate Start time
      long startTime = System.currentTimeMillis();

      // Increment 1000 times
      System.out.println("Incrementing");
      for (int i = 0 ; i < 1000 ; i++ )
      { counter.increment();
      }

      // Calculate stop time; print out statistics
      long stopTime = System.currentTimeMillis();
      System.out.println("Avg Ping = "
                       + ((stopTime - startTime)/1000f) + " msecs");
      System.out.println("Sum = " + counter.sum());
    } catch(org.omg.CORBA.SystemException e)
    { System.err.println("System Exception");
      System.err.println(e);
    }
  }
}
