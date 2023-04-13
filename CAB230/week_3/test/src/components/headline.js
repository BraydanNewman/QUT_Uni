import LikeCounter from "./likeCounter";

function Headline(prop) {
    return (
        <div>
            <h1>{prop.title}</h1>
            <LikeCounter />
        </div>
    )
}

export default Headline