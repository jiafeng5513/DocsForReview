package Counter;

/**
* Counter/CountHolder.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从count.idl
* 2012年4月10日 星期二 上午11时48分30秒 CST
*/

public final class CountHolder implements org.omg.CORBA.portable.Streamable
{
  public Counter.Count value = null;

  public CountHolder ()
  {
  }

  public CountHolder (Counter.Count initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = Counter.CountHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    Counter.CountHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return Counter.CountHelper.type ();
  }

}
