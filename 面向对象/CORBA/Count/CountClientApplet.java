// CountClientApplet.java  Applet Client, VisiBroker for Java
import java.awt.*;
import ContrastTheme;.
public class CountClientApplet extends java.applet.Applet
{ private TextField countField, pingTimeField;
  private Button runCount;
  private Counter.Count counter;
  public void init()
  { // Create a 2 by 2 grid of widgets.
    setLayout(new GridLayout(2, 2, 10, 10));

    // Add the four widgets, initialize where necessary
    add(new Label("Count"));
    add(countField = new TextField());
    countField.setText("1000");
    add(runCount = new Button("Run"));
    add(pingTimeField = new TextField());
    pingTimeField.setEditable(false);

    try
    { // Initialize the ORB.
      showStatus("Initializing the ORB");
      org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init(this, null);

      // Bind to the Count Object
      showStatus("Binding to Count Object");
      counter = Counter.CountHelper.bind(orb, "My Count");
    } catch(org.omg.CORBA.SystemException e)
    {
      showStatus("Applet Exception" + e);
      e.printStackTrace(System.out);
    }
  }

  public boolean action(Event ev, Object arg)
  { if(ev.target == runCount)
    { try
      { // Set Sum to initial value of 0
        showStatus("Setting Sum to 0");
        counter.sum((int)0);

        // get data from and set value of applet fields
        showStatus("Incrementing");
        int stopCount = Integer.parseInt(countField.getText());
        pingTimeField.setText(" ");

        // Calculate Start time
        long startTime = System.currentTimeMillis();

        // Increment stopCount times
        for (int i = 0 ; i < stopCount ; i++ )
        { counter.increment();
        }

        // Calculate stop time; show statistics
        long stopTime = System.currentTimeMillis();
        pingTimeField.setText("Avg Ping = "
                  + Float.toString((float)(stopTime- startTime)/stopCount)
                  + " msecs");
        showStatus("Sum = " + counter.sum());
      } catch(org.omg.CORBA.SystemException e)
      { showStatus("System Exception" + e);
      e.printStackTrace();
      }
      return true;
    }
    return false;
  }
}
