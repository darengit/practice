import java.io.*;
import java.util.*;

/*
 * Given a list of segments, as intervals with start and ends
 * merge all segments that overlap
 *
 */

public class Solution {
  public static void main(String[] args) {
    List<Segment> segments = new ArrayList<>();
    segments.add(new Segment(0,3));
    segments.add(new Segment(1,4));
    segments.add(new Segment(10,13));
    segments.add(new Segment(30,33));
    segments.add(new Segment(30,31));
    segments.add(new Segment(32,35));
    Set<Segment> mergedSegments = mergeSegments(segments);

    for (Segment mergedSegment: mergedSegments) {
      System.out.println(mergedSegment);
    }
  }
  
  private static Set<Segment> mergeSegments(List<Segment> segmentsList){
    Set<Segment> mergedSegments = new HashSet<>();
    for (Segment segment: segmentsList) {
      int mergedStart = segment.start;
      int mergedEnd = segment.end;

      // we iterate with an explicit iterator to mofidy mergedSegments
      // while looping through it
      List<Segment> segmentsToMerge = new ArrayList<>();
      Iterator<Segment> iter = mergedSegments.iterator();
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
      
      mergedSegments.add(new Segment(mergedStart, mergedEnd));
    }
    return mergedSegments;
  }

  // a static nested private class is for the simplicity of fitting into single file
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
