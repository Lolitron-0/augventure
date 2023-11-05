<template>
  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
  <div class="wrapper">
    <span class="bg-animate"></span>
    <span class="bg-animate2"></span>

    <div class="form-box register">
      <h2>Sign Up</h2>
      <form action="#">
        <div class="input-box">
          <input type="text" id="username" required>
          <label>Username</label>
          <i class='bx bxs-user' ></i>
        </div>
        <div class="input-box">
          <input type="text" id="email" required>
          <label>Email</label>
          <i class='bx bxs-envelope'></i>
        </div>
        <div class="input-box">
          <input type="password" id="password" required>
          <label>Password</label>
          <i class='bx bxs-lock-alt' ></i>
        </div>
        <button type="submit" @click="signupRequest()" class="btn">Sign Up</button>
        <div class="logreg-link">
          <p>Already have an account? <router-link to="login">Login</router-link></p>
        </div>
      </form>
    </div>
    <div class="info-text register">
      <h2>Join the 'Augventure' team</h2>
      <p>Augventure welcomes you!</p>
    </div>

  </div>

</template>

<script setup>

import { useRouter } from 'vue-router';
const router = useRouter()

function signupRequest() {
  var xhr = new XMLHttpRequest();
  var url = "/api/auth/signup";
  xhr.open("POST", url, true);
  xhr.setRequestHeader("Content-Type", "application/json");
  xhr.onreadystatechange = function () {
    alert(xhr.responseText)
    if (xhr.readyState === 4 &&
      xhr.status === 200 &&
      JSON.parse(xhr.responseText).result === "ok") {
      router.push("/login")
    }
  };
  var data = JSON.stringify({
    user: {
      username: document.getElementById("username").value,
      email: document.getElementById("email").value,
      password_hash: document.getElementById("password").value,
    },
  });
  xhr.send(data);
}

</script>

<style scoped>

* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: 'Poppins', sans-serif;
}

body {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background: #081b29;
}

.wrapper {
  position: relative;
  width: 750px;
  height: 450px;
  background: transparent;
  border: 2px solid #31a0a8;
  overflow: hidden;
}

.wrapper .form-box {
  position: absolute;
  top: 0;
  width: 50%;
  height: 100%;
  display: flex;flex-direction: column;
  justify-content: center;
}

.wrapper .form-box.register {
  right: 0;
  padding: 0 40px 0 60px;
}

.form-box h2 {
  font-size: 32px;
  color: #fff;
  text-align: center;
}

.form-box .input-box {
  position: relative;
  width: 100%;
  height: 50px;
  margin: 25px 0;
}


.input-box input{
  width: 100%;
  height: 100%;
  background: transparent;
  border: none;
  outline: none;
  border-bottom: 2px solid #fff;
  padding-right: 23px;
  font-size: 16px;
  color: #fff;
  font-weight: 500;
  transition: .5s;
}

.input-box input:focus,
.input-box input:valid {
  border-bottom-color: #32b8c2;
}

.input-box label {
  position: absolute;
  top: 50%;
  left: 0;
  transform: translateY(-50%);
  font-size: 16px;
  color: #fff;
  pointer-events: none;
  transition: .5s;
}

.input-box input:focus~label,
.input-box input:valid~label {
  top: -5px;
  color: #32b8c2;
}

.input-box i {
  position: absolute;
  top: 50%;
  right: 0;
  transform: translateY(-50%);
  font-size: 18px;
  color: #fff;
  transition: .5s;
}

.input-box input:focus~i,
.input-box input:valid~i {
  color: #32b8c2;
}

.btn {
  position: relative;
  width: 100%;
  height: 45px;
  background: transparent;
  border: 2px solid #32b8c2;
  outline: none;
  border-radius: 40px;
  cursor: pointer;
  font-size: 16px;
  color: #fff;
  font-weight: 600;
  z-index: 1;
  overflow: hidden;
}

.btn::before {
  content: '';
  position: absolute;
  top: -100%;
  left: 0;
  width: 100%;
  height: 300%;
  //background: linear-gradient(#081b29, #0ef, #081b29, #0ef);
  background: #32b8c2;
  z-index: -1;
  transition: .5s;
}

.btn:hover::before {
  top: 0;
}

.form-box .logreg-link{
  font-size: 14.5px;
  color: #fff;
  text-align: center;
  margin: 20px 0 10px;
}

.logreg-link p a{
  color: #32b8c2;
  text-decoration: none;
  font-weight: 600;
}

.logreg-link p a:hover{
  text-decoration: underline;
}

.wrapper .info-text {
  position: absolute;
  top: 0;
  width: 50%;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
}

.wrapper .info-text.register {
  left: 0;
  text-align: left;
  padding: 0 150px 60px 40px;
}

.info-text h2 {
  font-size: 36px;
  color: #fff;
  line-height: 1.3;
  text-transform: uppercase;
}

.info-text p {
  font-size: 16px;
  color: #fff;
}

.wrapper .bg-animate {
  position: absolute;
  top: -4px;
  right: 0;
  width: 850px;
  height: 600px;
  background: linear-gradient(45deg, #081b29, #32b8c2);
  border-bottom: 3px solid #32b8c2;
  transform: rotate(0) skewY(0);
  transform-origin: bottom right;
}

.wrapper .bg-animate2 {
  position: absolute;
  top: 100%;
  left: 250px;
  width: 850px;
  height: 700px;
  background: #081b29;
  border-top: 3px solid #32b8c2;
  transform: rotate(-11deg) skewY(-41deg);
  transform-origin: bottom left;
}
</style>