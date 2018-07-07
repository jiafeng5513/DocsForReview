// CountServer.java: The Count Server main program

class CountServer
{ static public void main(String[] args)
  { try
    { // Initialize the ORB
      org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init(args, null);

      // Initialize the BOA
      org.omg.CORBA.BOA boa = orb.BOA_init();

      // Create the Count object
      CountImpl count = new CountImpl("My Count");

      // Export to the ORB the newly created object
      boa.obj_is_ready(count);

      // Ready to service requests
      boa.impl_is_ready();
      }
      catch(org.omg.CORBA.SystemException e)
      { System.err.println(e);
      }
   }
}
