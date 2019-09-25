// #include <gst/gst.h>
#include <gstreamer-1.0/gst/gst.h>

//gcc src/test.cpp -o test `pkg-config --cflags --libs gstreamer-1.0`

int main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Build the pipeline */
//   pipeline =
//       gst_parse_launch
//       ("playbin uri=https://imdb-video.media-imdb.com/vi1822465049/MV5BY2NlMmJmMmQtMmNjZi00N2VhLWJlZDgtYTZjMjEzYTliNmEwXkExMV5BbXA0XkFpbWRiLWV0cy10cmFuc2NvZGU@.mp4?Expires=1569449713&Signature=uwjxplg-1DB3tkNbYyaVe6cWxixcXGgjK4xFzDNabDZM0gN3~7EYbUKlCMwOedZPBPqIp3uWQwMujaiXUnE0Wz~NgKNeNHC0lwPy4EYdlLTJ5Y~RAsFNIi61lmDsFBd12xTUScou4ZYAOndkh3fSJ6j9XE4wL5-LOascxww6bHiC1ZgdD~kAVFF1ZxL~f782dYvsDC2p8L-CxsHNYrKNjtdreNbU5V9iJLnwMZ7TXL-eXUwTCLoJyryFLUpe7-ArwHec-RMG04dnk9JsjKBe30Pi~H72TY95BEuy65eNlZAiXBMx8NCxD~Ur47~ny~3qUAg1XYhjHt64RvLAvNkB2A__&Key-Pair-Id=APKAIFLZBVQZ24NQH3KA",
//       NULL);


    pipeline =
      gst_parse_launch
      ("playbin uri=https://www.youtube.com/watch?v=6ziBFh3V1aM",
      NULL);


  /* Start playing */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);
  msg =
      gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
      GST_MESSAGE_ERROR);

  /* Free resources */
  if (msg != NULL)
    gst_message_unref (msg);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0;
}