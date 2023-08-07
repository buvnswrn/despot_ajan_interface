package de.dfki.asr.ajan.pluginsystem.mdpplugin.utils.POMDP.Connector;

import java.io.IOException;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;

public class ROSConnector {
    public static final int TAG_ACTION = 4;
    public static final int NUM_LASER_DIRECTIONS = 8;

    private static String postRequest(String URI) throws IOException {
        ResponseHandler<String> responseHandler= new BasicResponseHandler();
        CloseableHttpClient httpClient = HttpClients.createDefault();
        HttpPost httpPost = new HttpPost(URI);
        return httpClient.execute(httpPost, responseHandler);
    }
    public static String InitializeROSClient() throws IOException{
        String URI = "http://127.0.0.1:8000/AJAN/ros/initialize-service-client/?service_name=laser_tag_action_obs";
        return postRequest(URI);
    }

    public static String ExecuteAction(int action) throws IOException {
        String URI = "http://127.0.0.1:8000/AJAN/ros/call-service/?service_name=laser_tag_action_obs&action="+ action;
        return postRequest(URI);
    }

    public static long SetReading(long observation, long reading, long dir){
        final long ONE_ = 0x1;
        final int BITS_PER_READING_ = 0x7;
        observation &=  ~((ONE_<< BITS_PER_READING_-1)
                << (dir *BITS_PER_READING_));
        observation |= reading << (dir * BITS_PER_READING_);
        return observation;
    }

    public static int GetReading(int obs, int dir){
        final int ONE_ = 0x1;
        final int BITS_PER_READING_ = 0x7;
        return (obs>>(dir* BITS_PER_READING_) & (ONE_ <<BITS_PER_READING_ -1));
    }
}
