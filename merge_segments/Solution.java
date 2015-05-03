import java.io.*;
import java.util.*;

/*
 * Given a list of segments, as intervals with start and ends
 * merge all segments that overlap
 *
 */

public class Solution {
  public static void main(String[] args) {
    List<Segment> segmentsArray = new ArrayList<>();
    segmentsArray.add(new Segment(0,3));
    segmentsArray.add(new Segment(1,4));
    segmentsArray.add(new Segment(10,13));
    segmentsArray.add(new Segment(30,33));
    segmentsArray.add(new Segment(30,31));
    segmentsArray.add(new Segment(32,35));
    List<Segment> mergedSegments = mergeSegments(segmentsArray);

    for (Segment mergedSegment: mergedSegments) {
      System.out.println(mergedSegment);
    }
  }
  
  private static List<Segment> mergeSegments(List<Segment> segmentsArray){
    List<Segment> mergedSegmentsSoFar = new ArrayList<>();
    for (Segment segment: segmentsArray) {
      int mergedStart = segment.start;
      int mergedEnd = segment.end;
      
      List<Segment> segmentsToMerge = new ArrayList<>();
      Iterator<Segment> iter = mergedSegmentsSoFar.iterator();
      while(iter.hasNext()){
        Segment mergedSegment = iter.next();
        if (segment.overlap(mergedSegment)) {
          segmentsToMerge.add(mergedSegment);
          iter.remove();
        }
      }
      
      for (Segment segmentToMerge: segmentsToMerge) {
        if (segmentToMerge.start < mergedStart)
          mergedStart = segmentToMerge.start;
        if (segmentToMerge.end > mergedEnd)
          mergedEnd = segmentToMerge.end;
      }
      
      mergedSegmentsSoFar.add(new Segment(mergedStart, mergedEnd));
    }
    return mergedSegmentsSoFar;
  }
  
  static private class Segment {
    public int start;
    public int end;
  
    public Segment(int s, int e) {
      start = s;
      end = e;
    }
  
    public String toString(){
      return start + " " + end;
    }
    
    public Boolean overlap(Segment other) {
      if ((other.start >= start && other.start <= end) ||
          (other.end >= start && other.end <= end))
        return true;
      return false;
    }
  }
}
