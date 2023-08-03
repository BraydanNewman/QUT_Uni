import { Button, Form, FormGroup, Input, Label } from "reactstrap";
import { loginUser, registerUser } from "../../utils/authentication";
import { useNavigate } from "react-router-dom";
import React, { useContext, useState } from "react";
import {
  removeItemLs,
  setObjectLs,
  setStringLs,
} from "../../utils/localStorage";
import { EmailContext } from "../../App";

function Register() {
  const emailManager = useContext(EmailContext);
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState();
  let navigate = useNavigate();

  const handelTokenData = (tokenData) => {
    setObjectLs("bearerToken", tokenData["bearerToken"]);
    setObjectLs("refreshToken", tokenData["refreshToken"]);
    setStringLs("email", email);
    emailManager.setEmail(email);
    setError(null);
    navigate("/");
  };

  const handelLoginError = (error) => {
    removeItemLs("bearerToken");
    removeItemLs("refreshToken");
    removeItemLs("email");
    setError(error.message);
  };

  const handelRegisterError = (error) => {
    setError(error.message);
  };
  const handelRegisterSuccess = () => {
    loginUser(email, password, handelTokenData, handelLoginError);
    setError(null);
    navigate("/");
  };

  const registerUserSubmit = (event) => {
    event.preventDefault();
    password === event.target[2].value
      ? registerUser(
          email,
          password,
          handelRegisterSuccess,
          handelRegisterError
        )
      : setError("Password Doesn't Match");
  };

  return (
    <Form onSubmit={registerUserSubmit}>
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
        <Input
          id="passwordInput"
          type="password"
          name="password"
          onChange={(e) => setPassword(e.target.value)}
        />
      </FormGroup>
      <FormGroup>
        <Label for="password2Input">Confirm Password</Label>
        <Input id="password2Input" type="password" name="password2" />
      </FormGroup>
      {error ? <Label className="errorLabel">{error}</Label> : null}
      <br />
      <Button type="submit">Register</Button>
    </Form>
  );
}

export default Register;
