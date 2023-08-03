import React from "react";
import { Card, CardTitle, CardText, Row, Col, CardImg } from "reactstrap";

function Home() {
  return (
    <div className="text-light">
      <div className="m-5">
        <h1 className="m-1">WELCOME TO</h1>
        <h2 className="m-1">The Movie Searching Website!</h2>
        <h3 className="m-1">Search a Move I DEAR you!</h3>
        <button
          className="button m-2"
          onClick={() =>
            alert(
              "BAHA I do Nothing GOT YA!\nClick 'Movies' in the top right for the movies page"
            )
          }
        >
          Click Me ;)
        </button>
      </div>

      <Row className="m-2">
        <Col sm="6">
          <Card body>
            <CardTitle>Hahah Idk What to Say</CardTitle>
            <CardText>Legit Just looked up Neon Poster</CardText>
            <CardImg src="https://static.displate.com/280x392/displate/2021-02-15/54b3adc80014adacc24461118c55e17f_532309966708e68f5fc48a38a816e7ba.jpg" />
          </Card>
        </Col>
        <Col sm="6">
          <Card body>
            <CardTitle>This Could be a Movie.</CardTitle>
            <CardText>Except its not, they produce music.</CardText>
            <CardImg src="https://posterspy.com/wp-content/uploads/2015/04/NeonRobots2.jpg" />
          </Card>
        </Col>
      </Row>
      <Row className="m-2">
        <Col sm="6">
          <Card body>
            <CardTitle>Wish I had time to game.</CardTitle>
            <CardText>Except I'd only play Papa's Pizzeria</CardText>
            <CardImg src="https://storage.googleapis.com/pod_public/1300/120667.jpg" />
          </Card>
        </Col>
        <Col sm="6">
          <Card body>
            <CardTitle>Is this, No it can't be</CardTitle>
            <CardText>The very first Movie poster ona movie website</CardText>
            <CardImg src="https://m.media-amazon.com/images/I/71OIhbUOF-L._AC_UF894,1000_QL80_.jpg" />
          </Card>
        </Col>
      </Row>
    </div>
  );
}

export default Home;
