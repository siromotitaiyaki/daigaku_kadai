public class Song {
    
    private String name; // song name

    public Song(String name) { // Constructor
	this.name = name;
    }

    public final String getName() { // Getter
	return name;
    }
}