package Counter;
public interface Count extends org.omg.CORBA.Object {
  public void sum(int sum);
  public int sum();
  public int increment();
}
