public class assignment_5 {
    public static void main(String[] args) {

        VectorSet<Integer> nums = new VectorSet<>();
        nums.add(1);
        nums.add(2);
        nums.add(2);
        nums.add(3);
        nums.add(1);

        System.out.println(nums); // { 1 2 3 }

        VectorSet<String> words = new VectorSet<>();
        words.add("apple");
        words.add("banana");
        words.add("apple");
        words.add("orange");
        words.add("banana");

        System.out.println(words); // { apple banana orange }
    }
}