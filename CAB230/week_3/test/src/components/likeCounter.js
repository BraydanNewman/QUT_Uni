import {useState} from "react";

function LikeCounter() {
    const [count, setCount] = useState(0);
    const [superLikeCount, setSuperLikeCount] = useState(0);
    const superLike = () => {
        if (superLikeCount >= 2) {
            alert("NO MORE SUPER LIKES")
            return
        }
        setCount(count + 10)
        setSuperLikeCount(superLikeCount + 1)
    }

    return (
        <div>
            <p>Overall Likes: {count}</p>
            <button onClick={() => setCount(count + 1)}>Like</button>
            <button onClick={() => setCount(count - 1)}>Dislike</button>
            <button onClick={() => superLike()}>Super Like</button>
        </div>
    )
}

export default LikeCounter;