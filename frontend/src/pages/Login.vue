<!--<template>-->
<!--  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>-->
<!--  <div class="body_empty">-->
<!--    <div class="wrapper" @submit.prevent="login">-->
<!--      <span class="bg-animate"></span>-->

<!--      <div class="form-box login">-->
<!--        <h2>Login</h2>-->
<!--        <form action="#">-->
<!--          <div class="input-box">-->
<!--            <input id="email" type="text" required v-model.trim="user.email">-->
<!--            &lt;!&ndash; PROPERTY OF INPUT  :class="{ 'is-invalid': !$v.email.required }"  &ndash;&gt;-->

<!--            <label>Username</label>-->
<!--            <i class='bx bxs-user'></i>-->
<!--          </div>-->
<!--          <div class="input-box">-->
<!--            <input type="password" required v-model.trim="user.password">-->
<!--            &lt;!&ndash; :class="{ 'is-invalid': !$v.password.required }" &ndash;&gt;-->
<!--            <label>Password</label>-->
<!--            <i class='bx bxs-lock-alt'></i>-->
<!--          </div>-->
<!--&lt;!&ndash;              <router-link to="profile"><button type="submit" class="btn">Login</button></router-link>&ndash;&gt;-->
<!--          <button type="submit" class="btn">Login</button>-->
<!--          <div class="logreg-link">-->
<!--            <p>Don't have an account? <router-link to="register">Sign Up</router-link></p>-->
<!--          </div>-->
<!--        </form>-->
<!--      </div>-->
<!--      <div class="info-text login">-->
<!--        <h2>WELCOME BACK</h2>-->
<!--        <p>Augventure welcomes you!</p>-->
<!--      </div>-->

<!--    </div>-->
<!--  </div>-->
<!--</template>-->

<!--<script>-->
<!--import { email, required, minLength } from 'vuelidate/lib/validators'-->
<!--import { exportTypedArrayMethod } from "core-js/internals/array-buffer-view-core";-->
<!--import axios from 'axios'-->

<!--export default {-->
<!--  name: 'login',-->
<!--  data() {-->
<!--    return {-->
<!--      user: {-->
<!--        email: '',-->
<!--        password: ''-->
<!--      }-->
<!--    }-->
<!--  },-->
<!--  validations: {-->
<!--    user: {-->
<!--      email: { email, required },-->
<!--      password: { required, minLength: minLength(8) }-->
<!--    }-->
<!--  },-->
<!--  methods: {-->
<!--    async login() {-->
<!--      try {-->
<!--        const response = await this.$api.auth.login({-->
<!--          user: {-->
<!--            email: this.user.email,-->
<!--            password: this.user.password-->
<!--          }-->
<!--        });-->
<!--        const { token, user } = response.data;-->
<!--        localStorage.setItem('token', token);-->
<!--        // Сохраняем информацию о пользователе в хранилище, если это необходимо-->
<!--        // localStorage.setItem('user', JSON.stringify(user));-->
<!--        // Переход на другую страницу, например, профиль пользователя-->
<!--        this.$router.push({ name: 'profile' });-->
<!--      } catch (error) {-->
<!--        console.log(error.response.data);-->
<!--      }-->
<!--    }-->
<!--  }-->
<!--}-->
<!--</script>-->

<template>
  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
  <div class="body_empty">
    <div class="wrapper" @submit.prevent="login">
      <span class="bg-animate"></span>

      <div class="form-box login">
        <h2>Login</h2>
        <form action="#">
          <div class="input-box">
            <input id="email" type="text" required v-model.trim="user.email">
            <!-- PROPERTY OF INPUT  :class="{ 'is-invalid': !$v.email.required }"  -->

            <label>Email</label>
            <i class='bx bxs-user'></i>
          </div>
          <div class="input-box">
            <input type="password" required v-model.trim="user.password">
            <!-- :class="{ 'is-invalid': !$v.password.required }" -->
            <label>Password</label>
            <i class='bx bxs-lock-alt'></i>
          </div>
          <!--              <router-link to="profile"><button type="submit" class="btn">Login</button></router-link>-->
          <button type="submit" class="btn">Login</button>
          <div class="logreg-link">
            <p>Don't have an account? <router-link to="register">Sign Up</router-link></p>
          </div>
        </form>
      </div>
      <div class="info-text login">
        <h2>WELCOME BACK</h2>
        <p>Augventure welcomes you!</p>
      </div>

    </div>
  </div>
</template>

<script>
import { email, required, minLength } from 'vuelidate/lib/validators'
import { exportTypedArrayMethod } from "core-js/internals/array-buffer-view-core";
import axios from 'axios'

export default {
  name: 'login',
  data() {
    return {
      user: {
        email: '',
        password: ''
      }
    }
  },
  validations: {
    user: {
      email: { email, required },
      password: { required, minLength: minLength(8) }
    }
  },
  methods: {
    async login() {
      try {
        const response = await this.$api.auth.login({
          user: {
            email: this.user.email,
            password: this.user.password
          }
        });
        if (response && response.data) {
          const { token, user } = response.data;
          console.log(user);
          localStorage.setItem('token', token);
          localStorage.setItem('user', JSON.stringify(user));
          this.$router.push({ name: 'profile' });
        } else {
          console.log('Response data is undefined', response);
        }
      } catch (error) {

        console.log(error.message);
      }
    }
  }
}
</script>

<style scoped>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: 'Poppins', sans-serif;
}

.body_empty {
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
  /* box-shadow: 0 0 25px #0ef; */
  overflow: hidden;
}

.wrapper .form-box {
  position: absolute;
  top: 0;
  width: 50%;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
}

.wrapper .form-box.login {
  left: 0;
  padding: 0 60px 0 40px;
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


.input-box input {
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
  /* background: linear-gradient(#081b29, #0ef, #081b29, #0ef); */
  background: #32b8c2;
  z-index: -1;
  transition: .5s;
}

.btn:hover::before {
  top: 0;
}

.form-box .logreg-link {
  font-size: 14.5px;
  color: #fff;
  text-align: center;
  margin: 20px 0 10px;
}

.logreg-link p a {
  color: #32b8c2;
  text-decoration: none;
  font-weight: 600;
}

.logreg-link p a:hover {
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

.wrapper .info-text.login {
  right: 0;
  text-align: right;
  padding: 0 40px 60px 150px;
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
  transform: rotate(10deg) skewY(40deg);
  transform-origin: bottom right;
}
</style>