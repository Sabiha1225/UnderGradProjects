
package k_nearest_neighbour;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class Functions {
    private static Functions instance = null;
    public static Functions getInstance() {
      if(instance == null) {
         instance = new Functions();
      }
      return instance;
    }
    
    public void createHamiltonFeatureVectorForTrainingData()
    {
        Data data = Data.getInstance();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> trainingList = data.getDocList();
        for(int i=0; i<data.getDocCount(); ++i)
        {
            int vocCount=0;
            int hamiltonCount=0;
            int[] hamiltonFeature = new int[data.getVocabularyCount()];
            for(String key: vocabulary.keySet())
            {
                Document doc = trainingList.get(i);
                Map<String, Integer> map = doc.getMap();
                
                if(map.containsKey(key))
                {
                    hamiltonFeature[vocCount] = 1;
                    hamiltonCount++;
                }
                else
                {
                    hamiltonFeature[vocCount] = 0;
                }
                vocCount++;
            }
            /*for(int j=0; j<hamiltonFeature.length; ++j)
            {
                System.out.print(hamiltonFeature[j]+"   ");
            }
            System.out.println();
            System.out.println("----------------------------------------------------------------------------------------");
            System.out.println("----------------------------------------------------------------------------------------");
            
            */
            data.getDocList().get(i).setHamiltonFeatureVector(hamiltonFeature, data.getVocabularyCount());
            data.getDocList().get(i).setHamiltonCount(hamiltonCount);
        }
    }
    
    public void createHamiltonFeatureVectorForTestingData()
    {
        Data data = Data.getInstance();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> testingList = data.getTestDocList();
        for(int i=0; i<data.getTestDocCount(); ++i)
        {
            int vocCount=0;
            int hamiltonCount=0;
            int[] hamiltonFeature = new int[data.getVocabularyCount()];
            for(String key: vocabulary.keySet())
            {
                Document doc = testingList.get(i);
                Map<String, Integer> map = doc.getMap();
                
                if(map.containsKey(key))
                {
                    hamiltonFeature[vocCount] = 1;
                    hamiltonCount++;
                }
                else
                {
                    hamiltonFeature[vocCount] = 0;
                }
                vocCount++;
            }
            /*for(int j=0; j<hamiltonFeature.length; ++j)
            {
                System.out.print(hamiltonFeature[j]+"   ");
            }
            System.out.println();
            System.out.println("----------------------------------------------------------------------------------------");
            System.out.println("----------------------------------------------------------------------------------------");
            
            */
            data.getTestDocList().get(i).setHamiltonFeatureVector(hamiltonFeature, data.getVocabularyCount());
            data.getTestDocList().get(i).setHamiltonCount(hamiltonCount);
        }
    }
    
    public void getHamiltonDistance()
    {
        Data data = Data.getInstance();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> train = data.getDocList();
        List<Document> test = data.getTestDocList();
        for(int i=0; i<data.getTestDocCount(); ++i)
        {
            
            Document testDoc = test.get(i);
            List<Neighbor> neighbor = new ArrayList<Neighbor>();
            List<Neighbor> kNeighbor = new ArrayList<Neighbor>();
            int[] testHamilton = testDoc.getHamiltonFeatureVector();
            //System.out.println(testDoc.getTopic());
            for(int j=0; j<data.getDocCount(); ++j)
            {
                int distant = 0;
                Document trainDoc = train.get(j);
                int[] trainHamilton = trainDoc.getHamiltonFeatureVector();
                if(testDoc.getMap().size()==0)
                {
                    distant = trainDoc.getMap().size();
                }
                else if(trainDoc.getMap().size()==0)
                {
                    distant = testDoc.getHamiltonCount();
                }
                else
                {
                    /*for(int k=0; k<data.getVocabularyCount(); ++k)
                    {
                        if(testHamilton[k]!=trainHamilton[k])
                        {
                            distant++;
                        }
                    }*/
                    Map<String, Integer> map = trainDoc.getMap();
                    Map<String, Integer> map1 = testDoc.getMap();
                    
                    for(String key: map.keySet())
                    {
                        if(!map1.containsKey(key))
                        {
                            distant++;
                        }
                    }
                    for(String key: map1.keySet())
                    {
                        if(vocabulary.containsKey(key) && (!map.containsKey(key)))
                        {
                            distant++;
                        }
                    }
                }
                Neighbor n = new Neighbor();
                n.hamiltonDistance = distant;
                n.doc = trainDoc;
                neighbor.add(n);
            }
            Collections.sort(neighbor, new Comparator(){
                public int compare(Neighbor n1, Neighbor n2) {
                    return (n1.hamiltonDistance<n2.hamiltonDistance) ? -1 : 1;
                }

                @Override
                public int compare(Object t, Object t1) {
                    Neighbor n1 = (Neighbor) t;
                    Neighbor n2 = (Neighbor) t1;
                    return (n1.hamiltonDistance<n2.hamiltonDistance) ? -1 : 1;
                }
            });
            Map<String, Integer> map = new HashMap<String, Integer>();
            for(int l=0; l<data.K; ++l)
            {
                kNeighbor.add(neighbor.get(l));
                if(map.containsKey(neighbor.get(l).doc.getTopic()))
                {
                    int t = map.get(neighbor.get(l).doc.getTopic());
                    map.put(neighbor.get(l).doc.getTopic(), t+1);
                }
                else
                {
                    map.put(neighbor.get(l).doc.getTopic(), 1);
                }
            }
            data.getTestDocList().get(i).setkNeighbor(kNeighbor);
            
            List<String> helper = new ArrayList<String>();
            for(int l=0; l<data.K; ++l)
            {
                int value=0;
                if(map.containsKey(kNeighbor.get(l).doc.getTopic()))
                {
                    value = map.get(kNeighbor.get(l).doc.getTopic());
                    String s = kNeighbor.get(l).doc.getTopic()+" "+value;
                    if(!helper.contains(s))
                    {
                        helper.add(s);
                    }
                }
            }
            
            if(data.K==1)
            {
                data.getTestDocList().get(i).setHamiltonOutput(kNeighbor.get(0).doc.getTopic());
            }
            else
            {
                int max=0;
                String topic = "";
                for(int l=0; l<helper.size(); ++l)
                {
                    String x = helper.get(l);
                    String[] tokens = x.split(" ");
                    int d = Integer.parseInt(tokens[1]);
                    if(d>max)
                    {
                        max = d;
                        topic = tokens[0];
                    }
                }
                data.getTestDocList().get(i).setHamiltonOutput(topic);
            }
            /*for(int l=0; l<neighbor.size(); ++l)
            {
                System.out.println(neighbor.get(l).hamiltonDistance+"     "+neighbor.get(l).doc.getID());
            }*/
            /*System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            for(int l=0; l<data.K; ++l)
            {
                System.out.println(kNeighbor.get(l).hamiltonDistance+"     "+kNeighbor.get(l).doc.getID());
            }
            */
            
        }
    }
    
    public void createEuclideanFeatureVectorForTrainingData()
    {
        Data data = Data.getInstance();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> trainingList = data.getDocList();
        for(int i=0; i<data.getDocCount(); ++i)
        {
            int vocCount=0;
            int euclideanCount=0;
            int[] euclideanFeature = new int[data.getVocabularyCount()];
            for(String key: vocabulary.keySet())
            {
                Document doc = trainingList.get(i);
                Map<String, Integer> map = doc.getMap();
                
                if(map.containsKey(key))
                {
                    euclideanFeature[vocCount] = map.get(key);
                    euclideanCount++;
                }
                else
                {
                    euclideanFeature[vocCount] = 0;
                }
                vocCount++;
            }
            
            data.getDocList().get(i).setEuclideanFeatureVector(euclideanFeature);
            data.getDocList().get(i).setEuclideanCount(euclideanCount);
            
           /* for(int j=0; j<euclideanFeature.length; ++j)
            {
                System.out.print(euclideanFeature[j]+"   ");
            }
            System.out.println();
            System.out.println("----------------------------------------------------------------------------------------");
            System.out.println("----------------------------------------------------------------------------------------");
            Map<String, Integer> map1 = trainingList.get(0).getMap();
            
            for(String key: map1.keySet())
            {
                System.out.println(key+"   "+map1.get(key));
            }
            System.out.println("----------------------------------------------------------------------------------------");
            System.out.println(euclideanCount+"   "+map1.size());
           */
        }
    }
    
    public void createEuclideanFeatureVectorForTestingData()
    {
        Data data = Data.getInstance();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> testingList = data.getTestDocList();
        for(int i=0; i<data.getTestDocCount(); ++i)
        {
            int vocCount=0;
            int euclideanCount=0;
            int[] euclideanFeature = new int[data.getVocabularyCount()];
            for(String key: vocabulary.keySet())
            {
                Document doc = testingList.get(i);
                Map<String, Integer> map = doc.getMap();
                
                if(map.containsKey(key))
                {
                    euclideanFeature[vocCount] = map.get(key);
                    euclideanCount++;
                }
                else
                {
                    euclideanFeature[vocCount] = 0;
                }
                vocCount++;
            }
            
            data.getTestDocList().get(i).setEuclideanFeatureVector(euclideanFeature);
            data.getTestDocList().get(i).setEuclideanCount(euclideanCount);
            
            /*for(int j=0; j<hamiltonFeature.length; ++j)
            {
                System.out.print(hamiltonFeature[j]+"   ");
            }
            System.out.println();
            System.out.println("----------------------------------------------------------------------------------------");
            System.out.println("----------------------------------------------------------------------------------------");
            
            */
        }
    }
    
    public void getEuclideanDistance()
    {
        Data data = Data.getInstance();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> train = data.getDocList();
        List<Document> test = data.getTestDocList();
        for(int i=0; i<data.getTestDocCount(); ++i)
        {
            //if(i>0)
            //    break;
            
            Document testDoc = test.get(i);
            List<Neighbor> neighbor = new ArrayList<Neighbor>();
            List<Neighbor> kEuclideanNeighbor = new ArrayList<Neighbor>();
            int[] testEuclidean = testDoc.getEuclideanFeatureVector();
            //System.out.println(testDoc.getTopic());
            for(int j=0; j<data.getDocCount(); ++j)
            {
                double distant = 0.0;
                Document trainDoc = train.get(j);
                int[] trainEuclidean = trainDoc.getEuclideanFeatureVector();
                if(testDoc.getMap().size()==0 && trainDoc.getMap().size()==0)
                {
                    distant = 0.0;
                }
                else if((testDoc.getMap().size()==0) && (trainDoc.getMap().size()!=0))
                {
                    Map<String, Integer> map = trainDoc.getMap();
                    double sum=0;
                    for(String key: map.keySet())
                    {
                        int t = map.get(key);
                        sum += (double)(t*t);
                    }
                    distant = Math.sqrt(sum);
                }
                else if((testDoc.getMap().size()!=0) && (trainDoc.getMap().size()==0))
                {
                    Map<String, Integer> map = testDoc.getMap();
                    double sum=0;
                    for(String key: map.keySet())
                    {
                        if(vocabulary.containsKey(key))
                        {
                            int t = map.get(key);
                            sum += (double)(t*t);
                        }
                    }
                    distant = Math.sqrt(sum);
                }
                else
                {
                    /*for(int k=0; k<data.getVocabularyCount(); ++k)
                    {
                        if(testHamilton[k]!=trainHamilton[k])
                        {
                            distant++;
                        }
                    }*/
                    Map<String, Integer> map = trainDoc.getMap();
                    Map<String, Integer> map1 = testDoc.getMap();
                    double sum=0;
                    for(String key: map.keySet())
                    {
                        if(map1.containsKey(key))
                        {
                            int t = map.get(key);
                            int t1 = map1.get(key);
                            sum += (double)((t-t1)*(t-t1));
                        }
                        else
                        {
                            int t = map.get(key);
                            sum += (double)t*t;
                        }
                    }
                    for(String key: map1.keySet())
                    {
                        if(vocabulary.containsKey(key) && (!map.containsKey(key)))
                        {
                            int t = map1.get(key);
                            sum += (double)t*t;
                        }
                    }
                    distant = Math.sqrt(sum);
                }
                Neighbor n = new Neighbor();
                n.euclideanDistance = distant;
                n.doc = trainDoc;
                neighbor.add(n);
            }
            Collections.sort(neighbor, new Comparator(){
                /*public int compare(Neighbor n1, Neighbor n2) {
                    return (n1.euclideanDistance<n2.euclideanDistance) ? -1 : 1;
                }*/

                @Override
                public int compare(Object t, Object t1) {
                    Neighbor n1 = (Neighbor) t;
                    Neighbor n2 = (Neighbor) t1;
                    if(n1.euclideanDistance<n2.euclideanDistance)return -1;
                    if(n1.euclideanDistance>n2.euclideanDistance)return 1;
                    long thisBits = Double.doubleToLongBits(n1.euclideanDistance);
                    long anotherBits = Double.doubleToLongBits(n2.euclideanDistance);
                    return (thisBits == anotherBits ?  0 :(thisBits < anotherBits ? -1 : 1));
                }
            });
            Map<String, Integer> map = new HashMap<String, Integer>();
            for(int l=0; l<data.K; ++l)
            {
                kEuclideanNeighbor.add(neighbor.get(l));
                if(map.containsKey(neighbor.get(l).doc.getTopic()))
                {
                    int t = map.get(neighbor.get(l).doc.getTopic());
                    map.put(neighbor.get(l).doc.getTopic(), t+1);
                }
                else
                {
                    map.put(neighbor.get(l).doc.getTopic(), 1);
                }
            }
            data.getTestDocList().get(i).setkEuclideanNeighbor(kEuclideanNeighbor);
            
            List<String> helper = new ArrayList<String>();
            for(int l=0; l<data.K; ++l)
            {
                int value=0;
                if(map.containsKey(kEuclideanNeighbor.get(l).doc.getTopic()))
                {
                    value = map.get(kEuclideanNeighbor.get(l).doc.getTopic());
                    String s = kEuclideanNeighbor.get(l).doc.getTopic()+" "+value;
                    if(!helper.contains(s))
                    {
                        helper.add(s);
                    }
                }
            }
            
            if(data.K==1)
            {
                data.getTestDocList().get(i).setEuclideanOutput(kEuclideanNeighbor.get(0).doc.getTopic());
            }
            else
            {
                int max=0;
                String topic = "";
                for(int l=0; l<helper.size(); ++l)
                {
                    String x = helper.get(l);
                    String[] tokens = x.split(" ");
                    int d = Integer.parseInt(tokens[1]);
                    if(d>max)
                    {
                        max = d;
                        topic = tokens[0];
                    }
                }
                data.getTestDocList().get(i).setEuclideanOutput(topic);
            }
            /*for(int l=0; l<neighbor.size(); ++l)
            {
                System.out.println(neighbor.get(l).euclideanDistance+"     "+neighbor.get(l).doc.getID());
            }
            System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            for(int l=0; l<data.K; ++l)
            {
                System.out.println(kEuclideanNeighbor.get(l).euclideanDistance+"     "+kEuclideanNeighbor.get(l).doc.getID());
            }*/
            
            
        }
    }
    
    public void generateIDF()
    {
        Data data =  Data.getInstance();
        int totalDocCount = data.getDocCount();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> trainingList = data.getDocList();
        Map<String, Double> IDF = new HashMap<String, Double>();
        
        for(String key: vocabulary.keySet())
        {
            int counter = 0;
            for(int i=0; i<data.getDocCount(); ++i)
            {
                Document doc = trainingList.get(i);
                Map<String, Integer> map = doc.getMap();
                if(map.containsKey(key))
                    counter++;
            }
            IDF.put(key, Math.log(totalDocCount/counter));
        }
        data.setIDF(IDF);
    }
    
    public void getCosineSimilarities()
    {
        Data data = Data.getInstance();
        Map<String, Integer> vocabulary = data.getVocabulary();
        List<Document> train = data.getDocList();
        List<Document> test = data.getTestDocList();
        Map<String, Double> IDF = data.getIDF();
        
        for(int i=0; i<data.getTestDocCount(); ++i)
        {
            
            Document testDoc = test.get(i);
            List<Neighbor> neighbor = new ArrayList<Neighbor>();
            List<Neighbor> kCosineNeighbor = new ArrayList<Neighbor>();
            
            //System.out.println(testDoc.getTopic());
            for(int j=0; j<data.getDocCount(); ++j)
            {
                double distant = 0.0;
                Document trainDoc = train.get(j);
                
                if(testDoc.getMap().size()==0 || trainDoc.getMap().size()==0)
                {
                    distant = 0.0;
                }
                else
                {
                    Map<String, Integer> map = trainDoc.getMap();
                    Map<String, Integer> map1 = testDoc.getMap();
                    double sum=0.0;
                    double trainMod=0.0, testMod=0.0, train_TF_IDF=0.0, test_TF_IDF=0.0;
                    for(String key: map.keySet())
                    {
                        train_TF_IDF = (((double)map.get(key))/trainDoc.getTotalWord())*IDF.get(key);
                        if(map1.containsKey(key))
                        {
                            test_TF_IDF = (((double)map1.get(key))/testDoc.getTotalWord())*IDF.get(key);
                            sum += (train_TF_IDF*test_TF_IDF);
                            testMod += (test_TF_IDF*test_TF_IDF);
                        }
                        trainMod += (train_TF_IDF*train_TF_IDF);
                    }
                    for(String key: map1.keySet())
                    {
                        if(vocabulary.containsKey(key) && (!map.containsKey(key)))
                        {
                            test_TF_IDF = (((double)map1.get(key))/testDoc.getTotalWord())*IDF.get(key);
                            testMod += (test_TF_IDF*test_TF_IDF);
                        }
                    }
                    distant = sum/((Math.sqrt(trainMod))*(Math.sqrt(testMod)));
                }
                Neighbor n = new Neighbor();
                n.cosineSimilarity = distant;
                n.doc = trainDoc;
                neighbor.add(n);
            }
            Collections.sort(neighbor, new Comparator(){

                @Override
                public int compare(Object t, Object t1) {
                    Neighbor n1 = (Neighbor) t;
                    Neighbor n2 = (Neighbor) t1;
                    if(n1.cosineSimilarity<n2.cosineSimilarity)return 1;
                    if(n1.cosineSimilarity>n2.cosineSimilarity)return -1;
                    long thisBits = Double.doubleToLongBits(n1.cosineSimilarity);
                    long anotherBits = Double.doubleToLongBits(n2.cosineSimilarity);
                    return (thisBits == anotherBits ?  0 :(thisBits < anotherBits ? 1 : -1));
                }
            });
            Map<String, Integer> map = new HashMap<String, Integer>();
            for(int l=0; l<data.K; ++l)
            {
                kCosineNeighbor.add(neighbor.get(l));
                if(map.containsKey(neighbor.get(l).doc.getTopic()))
                {
                    int t = map.get(neighbor.get(l).doc.getTopic());
                    map.put(neighbor.get(l).doc.getTopic(), t+1);
                }
                else
                {
                    map.put(neighbor.get(l).doc.getTopic(), 1);
                }
            }
            data.getTestDocList().get(i).setkCosineNeighbor(kCosineNeighbor);
            
            List<String> helper = new ArrayList<String>();
            for(int l=0; l<data.K; ++l)
            {
                int value=0;
                if(map.containsKey(kCosineNeighbor.get(l).doc.getTopic()))
                {
                    value = map.get(kCosineNeighbor.get(l).doc.getTopic());
                    String s = kCosineNeighbor.get(l).doc.getTopic()+" "+value;
                    if(!helper.contains(s))
                    {
                        helper.add(s);
                    }
                }
            }
            
            if(data.K==1)
            {
                data.getTestDocList().get(i).setCosineOutput(kCosineNeighbor.get(0).doc.getTopic());
            }
            else
            {
                int max=0;
                String topic = "";
                for(int l=0; l<helper.size(); ++l)
                {
                    String x = helper.get(l);
                    String[] tokens = x.split(" ");
                    int d = Integer.parseInt(tokens[1]);
                    if(d>max)
                    {
                        max = d;
                        topic = tokens[0];
                    }
                }
                data.getTestDocList().get(i).setCosineOutput(topic);
            }
            /*
            for(int l=0; l<neighbor.size(); ++l)
            {
                System.out.println(neighbor.get(l).cosineSimilarity+"     "+neighbor.get(l).doc.getID());
            }
            System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            for(int l=0; l<data.K; ++l)
            {
                System.out.println(kCosineNeighbor.get(l).cosineSimilarity+"     "+kCosineNeighbor.get(l).doc.getID());
            }*/
        }
            
    }
}
