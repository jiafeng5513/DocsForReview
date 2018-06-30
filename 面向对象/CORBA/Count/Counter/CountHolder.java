package Counter;
final public class CountHolder implements org.omg.CORBA.portable.Streamable {
  public Counter.Count value;
  public CountHolder() {
  }
  public CountHolder(Counter.Count value) {
    this.value = value;
  }
  public void _read(org.omg.CORBA.portable.InputStream input) {
    value = CountHelper.read(input);
  }
  public void _write(org.omg.CORBA.portable.OutputStream output) {
    CountHelper.write(output, value);
  }
  public org.omg.CORBA.TypeCode _type() {
    return CountHelper.type();
  }
}
