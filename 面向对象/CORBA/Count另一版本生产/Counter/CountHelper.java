package Counter;


/**
* Counter/CountHelper.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从count.idl
* 2012年4月10日 星期二 上午11时48分30秒 CST
*/

abstract public class CountHelper
{
  private static String  _id = "IDL:Counter/Count:1.0";

  public static void insert (org.omg.CORBA.Any a, Counter.Count that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static Counter.Count extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      __typeCode = org.omg.CORBA.ORB.init ().create_interface_tc (Counter.CountHelper.id (), "Count");
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static Counter.Count read (org.omg.CORBA.portable.InputStream istream)
  {
    return narrow (istream.read_Object (_CountStub.class));
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, Counter.Count value)
  {
    ostream.write_Object ((org.omg.CORBA.Object) value);
  }

  public static Counter.Count narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof Counter.Count)
      return (Counter.Count)obj;
    else if (!obj._is_a (id ()))
      throw new org.omg.CORBA.BAD_PARAM ();
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      Counter._CountStub stub = new Counter._CountStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

  public static Counter.Count unchecked_narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof Counter.Count)
      return (Counter.Count)obj;
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      Counter._CountStub stub = new Counter._CountStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

}
