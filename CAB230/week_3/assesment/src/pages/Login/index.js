import React, { useContext, useState } from "react";
import { Button, Form, FormGroup, Input, Label } from "reactstrap";
import { loginUser } from "../../utils/authentication";
import { useNavigate, useSearchParams } from "react-router-dom";
import {
  removeItemLs,
  setObjectLs,
  setStringLs,
} from "../../utils/localStorage";
import { EmailContext } from "../../App";

function Login() {
  const emailManager = useContext(EmailContext);
  const [searchParams] = useSearchParams();
  let navigate = useNavigate();
  const [error, setError] = useState(searchParams.get("error"));
  const [email, setEmail] = useState("");

  const handelTokenData = (tokenData) => {
    setObjectLs("bearerToken", tokenData["bearerToken"]);
    setObjectLs("refreshToken", tokenData["refreshToken"]);
    setStringLs("email", email);
    emailManager.setEmail(email);
    setError(null);
    if (searchParams.get("deepBack") === "1") navigate(-4);
    else navigate(-1);
  };

  const handelLoginError = (error) => {
    removeItemLs("bearerToken");
    removeItemLs("refreshToken");
    removeItemLs("email");
    setError(error.message);
  };

  const loginUserSubmit = (event) => {
    event.preventDefault();
    const password = event.target[1].value;
    loginUser(email, password, handelTokenData, handelLoginError);
  };

  return (
    <Form onSubmit={loginUserSubmit}>
      <FormGroup>
        <Label for="emailInput">Email</Label>
        <Input
          id="emailInput"
          type="email"
          name="email"
          onChange={(e) => setEmail(e.target.value)}
        />
      </FormGroup>
      <FormGroup>
        <Label for="passwordInput">Password</Label>
        <Input id="passwordInput" type="password" name="password" />
      </FormGroup>

      {error ? <Label className="errorLabel">{error}</Label> : null}
      <br />
      <Button type="submit">Login</Button>
    </Form>
  );
}

export default Login;
