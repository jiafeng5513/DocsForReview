package Counter;


/**
* Counter/CountPOA.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从count.idl
* 2012年4月10日 星期二 上午11时48分30秒 CST
*/

public abstract class CountPOA extends org.omg.PortableServer.Servant
 implements Counter.CountOperations, org.omg.CORBA.portable.InvokeHandler
{

  // Constructors

  private static java.util.Hashtable _methods = new java.util.Hashtable ();
  static
  {
    _methods.put ("_get_sum", new java.lang.Integer (0));
    _methods.put ("_set_sum", new java.lang.Integer (1));
    _methods.put ("increment", new java.lang.Integer (2));
  }

  public org.omg.CORBA.portable.OutputStream _invoke (String $method,
                                org.omg.CORBA.portable.InputStream in,
                                org.omg.CORBA.portable.ResponseHandler $rh)
  {
    org.omg.CORBA.portable.OutputStream out = null;
    java.lang.Integer __method = (java.lang.Integer)_methods.get ($method);
    if (__method == null)
      throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);

    switch (__method.intValue ())
    {
       case 0:  // Counter/Count/_get_sum
       {
         int $result = (int)0;
         $result = this.sum ();
         out = $rh.createReply();
         out.write_long ($result);
         break;
       }

       case 1:  // Counter/Count/_set_sum
       {
         int newSum = in.read_long ();
         this.sum (newSum);
         out = $rh.createReply();
         break;
       }

       case 2:  // Counter/Count/increment
       {
         int $result = (int)0;
         $result = this.increment ();
         out = $rh.createReply();
         out.write_long ($result);
         break;
       }

       default:
         throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);
    }

    return out;
  } // _invoke

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:Counter/Count:1.0"};

  public String[] _all_interfaces (org.omg.PortableServer.POA poa, byte[] objectId)
  {
    return (String[])__ids.clone ();
  }

  public Count _this() 
  {
    return CountHelper.narrow(
    super._this_object());
  }

  public Count _this(org.omg.CORBA.ORB orb) 
  {
    return CountHelper.narrow(
    super._this_object(orb));
  }


} // class CountPOA
